void GetAudio(){        
  // Before we start any recording we stop any earlier Audio Output or streaming (e.g. radio)
  if (audio_play.isRunning()) {
    audio_play.connecttohost("");  // 'audio_play.stopSong()' wouldn't be enough (STT wouldn't reconnect)
  }
    //Start Recording
  Record_Start(AUDIO_FILE);
  const long starttime = millis();

  if (digitalRead(TOUCH_INT) == HIGH){
    Record_Stop(AUDIO_FILE);
  }

  float recorded_seconds;

  if (Record_Available(AUDIO_FILE, &recorded_seconds))  //  true once when recording finalized (.wav file available)
  {
    if (recorded_seconds > 0.4)  // ignore short btn TOUCH (e.g. <0.4 secs, used for 'audio_play.stopSong' only)
    {
      String transcription = SpeechToText_Deepgram(AUDIO_FILE);

      String again = "Please Ask Again . . . . . . . . . . . ";

      Serial.println(transcription);
      if (transcription == "") {
        speakTextInChunks(again, 93); 
        Serial.println("Please Ask Again");
        while (audio_play.isRunning())  // wait here until finished (just for Demo purposes, before we play Demo 4)
        {
          audio_play.loop();
        }
        goto here;
      }

      WiFiClientSecure client;
      client.setInsecure();  // Disable SSL verification for simplicity (not recommended for production)
      String Answer = "";    // Declare Answer variable here

      text = "";

      if (client.connect("generativelanguage.googleapis.com", 443)) {
        String url = "/v1beta/models/gemini-3.1-flash:generateContent?key=" + String(gemini_KEY);
        String payload = String("{\"contents\": [{\"parts\":[{\"text\":\"" + transcription + "\"}]}],\"generationConfig\": {\"maxOutputTokens\": " + Gemini_Max_Token + "}}");
       // Send the HTTP POST request
        client.println("POST " + url + " HTTP/1.1");
        client.println("Host: generativelanguage.googleapis.com");
        client.println("Content-Type: application/json");
        client.print("Content-Length: ");
        client.println(payload.length());
        client.println();
        client.println(payload);

        // Read the response
        String response;
        while (client.connected()) {
          String line = client.readStringUntil('\n');
          if (line == "\r") {
            break;
          }
        }

        // Read the actual response
        response = client.readString();
        parseResponse(response);
      } else {
        Serial.println("Connection failed!");
      }

      client.stop();  // End the connection
      //----------------------------------------------------

      if (filteredAnswer != "")  // we found spoken text .. now starting Demo examples:
      {
        Serial.print("AI speaking: ");
        Serial.println(filteredAnswer);
        speakTextInChunks(filteredAnswer, 93); 
      }
    }
  }
}



void GetVision(){
    camera_fb_t *fb = esp_camera_fb_get();
    if (!fb) {
      Serial.println("Failed to get camera frame buffer");
      return;
    }

      char filename[32];
      sprintf(filename, "/image%d.jpg");
      // Save photo to file
      writeFile(SD, filename, fb->buf, fb->len);
      Serial.printf("Saved picture：%s\n", filename);
    }

    uint8_t* buf = fb->buf;
    uint32_t len = fb->len;
    tft.startWrite();
    tft.setAddrWindow(0, 0, camera_width, camera_height);
    tft.pushColors(buf, len);
    tft.endWrite();

    esp_camera_fb_return(fb);
}

void uploadImageFromSD(const char* filePath, WiFiClientSecure &client) {
  // 1. Open the image file from SD card in READ mode
  File imgFile = SD.open(filePath, FILE_READ);
  
  if (!imgFile) {
    Serial.println("Failed to open image file!");
    return;
  }

  // 2. Get the exact file size for the HTTP header
  size_t imageLength = imgFile.size();
  Serial.print("Sending image size: ");
  Serial.println(imageLength);

  // 3. Send HTTP POST headers
  client.println("POST " + url + " HTTP/1.1");
  client.println("Host: generativelanguage.googleapis.com");
  client.println("Content-Type: image/jpeg"); // Change if using PNG
  client.print("Content-Length: ");
  client.println(imageLength);
  client.println("Connection: close");
  client.println(); // Mandatory blank line separating headers from body

  // 4. Stream the binary data in chunks to save RAM
  const size_t bufferSize = 1024; // 1 KB chunks
  uint8_t buffer[bufferSize];

  while (imgFile.available()) {
    // Read a chunk from the SD card
    int bytesRead = imgFile.read(buffer, bufferSize);
    
    // Write the exact number of bytes read directly to the network client
    client.write(buffer, bytesRead);
  }

  // 5. Clean up
  imgFile.close();
  Serial.println("Image transmission complete.");
}
void speakTextInChunks(String text, int maxLength) {
  int start = 0;
  while (start < text.length()) {
    int end = start + maxLength;

    // Ensure we don't split in the middle of a word
    if (end < text.length()) {
      while (end > start && text[end] != ' ' && text[end] != '.' && text[end] != ',') {
        end--;
      }
    }

    // If no space or punctuation is found, just split at maxLength
    if (end == start) {
      end = start + maxLength;
    }

    String chunk = text.substring(start, end);
    audio_play.connecttospeech(chunk.c_str(), TTS_GOOGLE_LANGUAGE);

    while (audio_play.isRunning()) {
      audio_play.loop();
      if (digitalRead(pin_RECORD_BTN) == LOW) {
        break;
      }
    }

    start = end + 1;  // Move to the next part, skipping the space
                      // delay(200);       // Small delay between chunks
  }
}

void parseResponse(String response) {
  repeat = "";
  // Extract JSON part from the response
  int jsonStartIndex = response.indexOf("{");
  int jsonEndIndex = response.lastIndexOf("}");

  if (jsonStartIndex != -1 && jsonEndIndex != -1) {
    String jsonPart = response.substring(jsonStartIndex, jsonEndIndex + 1);
    // Serial.println("Clean JSON:");
    // Serial.println(jsonPart);

    DynamicJsonDocument doc(1024);  // Increase size if needed
    DeserializationError error = deserializeJson(doc, jsonPart);

    if (error) {
      Serial.print("DeserializeJson failed: ");
      Serial.println(error.c_str());
      return;
    }

    if (doc.containsKey("candidates")) {
      for (const auto& candidate : doc["candidates"].as<JsonArray>()) {
        if (candidate.containsKey("content") && candidate["content"].containsKey("parts")) {

          for (const auto& part : candidate["content"]["parts"].as<JsonArray>()) {
            if (part.containsKey("text")) {
              text += part["text"].as<String>();
            }
          }
          text.trim();
          // Serial.print("Extracted Text: ");
          // Serial.println(text);
          filteredAnswer = "";
          for (size_t i = 0; i < text.length(); i++) {
            char c = text[i];
            if (isalnum(c) || isspace(c) || c == ',' || c == '.' || c == '\'') {
              filteredAnswer += c;
            } else {
              filteredAnswer += ' ';
            }
          }
          // filteredAnswer = text;
          // Serial.print("FILTERED - ");
          //Serial.println(filteredAnswer);

          repeat = filteredAnswer;
        }
      }
    } else {
      Serial.println("No 'candidates' field found in JSON response.");
    }
  } else {
    Serial.println("No valid JSON found in the response.");
  }
}

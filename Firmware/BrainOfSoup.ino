// Face recog -> greet
// Called name ->
  // Get input (audio & video(if requested))
  // Response (audio) + face (hardcode)

#include <Arduino.h>
#include <WiFi.h>
#include <TFT_eSPI.h>
#include <HTTPClient.h>
#include <SPI.h>
#include <Audio.h>
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "esp_camera.h"
#include "camera_pins.h"

#define AUDIO_FILE "/Audio.wav"
#define TTS_GOOGLE_LANGUAGE "en-IN"

#define CAMERA_MODEL_XIAO_ESP32S3
#define TOUCH_INT D7
#define BOARD_SCREEN_COMBO 501

Audio audio_play;

bool I2S_Record_Init();
bool Record_Start(String filename);
bool Record_Available(String filename, float* audiolength_sec);

String SpeechToText_Deepgram(String filename);
void Deepgram_KeepAlive();
const float adcMax = 4095.0;           // Max value for ADC on ESP32
const float vRef = 3.4;                // Reference voltage for ESP32
const int numSamples = 100;            // Number of samples for averaging
const float calibrationFactor = 1.48;  // Calibration factor for ADC reading

const char* ssid = ;
const char* password = ;
const char* Gemini_API_Key = ;
const char* Gemini_Max_Token = ;
String res = "";


static camera_config_t camera_example_config = {
        .pin_pwdn       = PWDN_GPIO_NUM,
        .pin_reset      = RESET_GPIO_NUM,
        .pin_xclk       = XCLK_GPIO_NUM,
        .pin_sccb_sda   = SIOD_GPIO_NUM,
        .pin_sccb_scl   = SIOC_GPIO_NUM,
        .pin_d7         = Y9_GPIO_NUM,
        .pin_d6         = Y8_GPIO_NUM,
        .pin_d5         = Y7_GPIO_NUM,
        .pin_d4         = Y6_GPIO_NUM,
        .pin_d3         = Y5_GPIO_NUM,
        .pin_d2         = Y4_GPIO_NUM,
        .pin_d1         = Y3_GPIO_NUM,
        .pin_d0         = Y2_GPIO_NUM,
        .pin_vsync      = VSYNC_GPIO_NUM,
        .pin_href       = HREF_GPIO_NUM,
        .pin_pclk       = PCLK_GPIO_NUM,

        .xclk_freq_hz   = 20000000, // The clock frequency of the image sensor
        .fb_location = CAMERA_FB_IN_PSRAM; // Set the frame buffer storage location
        .pixel_format   = PIXFORMAT_JPEG, // The pixel format of the image: PIXFORMAT_ + YUV422|GRAYSCALE|RGB565|JPEG
        .frame_size     = FRAMESIZE_UXGA, // The resolution size of the image: FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
        .jpeg_quality   = 12, // The quality of the JPEG image, ranging from 0 to 63.
        .fb_count       = 2, // The number of frame buffers to use.
        .grab_mode      = CAMERA_GRAB_WHEN_EMPTY //  The image capture mode.
    };

// Width and height of round display
const int camera_width = 240;
const int camera_height = 240;

TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  WiFi.begin(ssid, password);
  Serial.println("Connecting to: ");
  Serial.print(ssid);
  if (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("CONNECTED!")
    Serial.println("IP address: ")
    Serial.print(WiFi.localIP());
  }
  // Initialize SD card
  if (!SD.begin()) {
    Serial.println("ERROR - SD Card initialization failed!");
    return;
  }
  // Initialize Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error", err);
    return;
  }
  // initialize KALO I2S Recording Services
  I2S_Record_Init();

  // INIT Audio Output (via Audio.h, see here: https://github.com/schreibfaul1/ESP32-audioI2S)
  audio_play.setPinout(pin_I2S_BCLK, pin_I2S_LRC, pin_I2S_DOUT);

  audio_play.setVolume(21);  //21

  // INIT done, starting user interaction
  Serial.println("Call me Soup!");
}

void FaceRecognization(){
  camera_fb_t *fb = esp_camera_fb_get();
  
}

void loop() {
  lv_example_animimg_play();

  // Nmae called
  GetAudio();

  //Req to get vision
  GetVision();
  uploadImageFromSD();

  if (digitalRead(pin_RECORD_BTN) == HIGH && !audio_play.isRunning())  // but don't do it during recording or playing
  {
    static uint32_t millis_ping_before;
    if (millis() > (millis_ping_before + 5000)) {
      millis_ping_before = millis();
      led_RGB(0, 0, 0);  // short LED OFF means: 'Reconnection server, can't record in moment'
      Deepgram_KeepAlive();
    }
  }
}
  speakTextInChunks();
  parseResponse();
  
  String batt = "battery low. please charge";
  if (Timer.isReady()) {
    battry_filtering();
    Serial.print("Battery Voltage: ");
    Serial.println(batteryVoltage);
    if (batteryVoltage < 3.4) {
      speakTextInChunks(batt.c_str(), 93);
    }

    Timer.reset();
}
  battry_filtering();

}

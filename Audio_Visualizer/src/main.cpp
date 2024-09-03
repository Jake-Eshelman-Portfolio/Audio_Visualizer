// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-4: Using The Microphone
#include <ILI9341_t3.h>
#include <font_Arial.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>
#include <Bounce.h>

///////////////////////////////////
// Audio objects
///////////////////////////////////

AudioInputI2S            i2s1;         // Audio input (from the microphone)
AudioOutputI2S           i2s2;         // Audio output (to headphones or line out)
AudioControlSGTL5000     sgtl5000_1;   // Control for the audio shield
AudioAnalyzeFFT1024      fft1024_1;    // FFT object for analysis

AudioConnection          patchCord0(i2s1, 0, fft1024_1, 0);  // Connect input to FFT
AudioConnection          patchCord1(i2s1, 0, i2s2, 0);  // Connect left channel
AudioConnection          patchCord2(i2s1, 1, i2s2, 1);  // Connect right channel

// LCD Setup
// LCD control pins defined by the baseboard
#define TFT_CS 40
#define TFT_DC  9

// Define Audio button location and size
#define AUDIO_X 10
#define AUDIO_Y 10
#define AUDIO_W 105
#define AUDIO_H 32
#define BUTTON_FONT Arial_14

// Use main SPI bus MOSI=11, MISO=12, SCK=13 with different control pins
ILI9341_t3 tft = ILI9341_t3(TFT_CS, TFT_DC);

// Array to store previous magnitudes for smoothing
float previousMagnitude[128] = {0};

void setup() {
  Serial.begin(9600); // may need to increase, 115200 in demo

  // Setup LCD screen
  tft.begin();
  tft.setRotation(3);  // Rotates screen to match the baseboard orientation

  // Setup audio system
  AudioMemory(12);  
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(50);

  delay(1000);
}

//===============================================================================
//  Main
//===============================================================================
void loop() {
  if (fft1024_1.available()) {
    tft.fillScreen(ILI9341_BLACK); // Clear screen for new frame

    for (int i = 0; i < 128; i++) {  // FFT bins range from 0-511, use a subset
      float magnitude = fft1024_1.read(i) * 650.0;  // Scale magnitude
      magnitude = 0.7 * previousMagnitude[i] + 0.3 * magnitude;  //  smoothing
      previousMagnitude[i] = magnitude;
      int height = map(magnitude, 0, 100, 0, tft.height());

      // Map height to color (e.g., low frequencies = blue, high = red)
      int color = tft.color565(map(i, 0, 127, 0, 255), map(i, 0, 127, 255, 0), map(i, 0, 127, 255, 0));

      // Draw a vertical bar for each bin. 2 pixels wide and 1 pixel spacing
      tft.fillRect(i * 3, tft.height() - height, 2, height, color);
    }
    // Add a short delay to reduce flickering and improve performance
    delay(20);  
  } else {
    Serial.println("FFT not available.");
  }
}

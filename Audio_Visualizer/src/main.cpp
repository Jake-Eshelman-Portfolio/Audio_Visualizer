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
void SetAudioButton();

void setup() {
  Serial.begin(9600); // may need to increase, 115200 in demo

  // Setup LCD screen
  tft.begin();
  tft.setRotation(3);  // Rotates screen to match the baseboard orientation


  AudioMemory(8);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.5);
  sgtl5000_1.inputSelect(AUDIO_INPUT_MIC);
  sgtl5000_1.micGain(36);
  delay(1000);
}

//===============================================================================
//  Main
//===============================================================================
void loop() {
  SetAudioButton();
}

void SetAudioButton ()
{
  tft.setCursor(AUDIO_X + 8, AUDIO_Y + 8);
  tft.setFont(BUTTON_FONT);
  tft.setTextColor(ILI9341_WHITE);

  tft.fillRoundRect(AUDIO_X, AUDIO_Y, AUDIO_W, AUDIO_H, 4, ILI9341_GREEN);
  tft.print ("Playing");
}
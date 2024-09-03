// Advanced Microcontroller-based Audio Workshop
//
// http://www.pjrc.com/store/audio_tutorial_kit.html
// https://hackaday.io/project/8292-microcontroller-audio-workshop-had-supercon-2015
// 
// Part 2-4: Using The Microphone

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

void setup() {
  Serial.begin(9600);
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
  // do nothing
}

#include "Sequencer.h"
#include "Clock.h"
#include "Drum_channel.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

AudioPlaySdWav SD1;

Drum_channel kick("KICK.WAV", 16, &SD1);

// GUItool: begin automatically generated code
//
//AudioPlaySdWav           playSdWav1;     //xy=157,475
//AudioPlaySdWav           playSdWav3;     //xy=157,475
//AudioPlaySdWav           playSdWav2;     //xy=167,364
//AudioMixer4              mixer3;         //xy=383,458
//AudioMixer4              mixer1;         //xy=385,251
//AudioMixer4              mixer2;         //xy=388,362
//AudioMixer4              mixer4;         //xy=643,361
//AudioOutputI2S           i2s1;           //xy=822,363
//AudioConnection          patchCord1(playSdWav3, 0, mixer3, 0);
//AudioConnection          patchCord2(playSdWav3, 0, mixer2, 2);
//AudioConnection          patchCord3(playSdWav3, 1, mixer1, 2);
//AudioConnection          patchCord4(playSdWav1, 0, mixer1, 0);
//AudioConnection          patchCord5(playSdWav1, 1, mixer2, 0);
//AudioConnection          patchCord6(playSdWav1, 1, mixer3, 2);
//AudioConnection          patchCord7(playSdWav2, 0, mixer1, 1);
//AudioConnection          patchCord8(playSdWav2, 1, mixer2, 1);
//AudioConnection          patchCord9(playSdWav2, 1, mixer3, 1);
//AudioConnection          patchCord10(mixer3, 0, mixer4, 2);
//AudioConnection          patchCord11(mixer1, 0, mixer4, 0);
//AudioConnection          patchCord12(mixer2, 0, mixer4, 1);
//AudioConnection          patchCord13(mixer4, 0, i2s1, 0);
//AudioConnection          patchCord14(mixer4, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=394.00000762939453,228.00003051757812

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

Sequencer sequence(5,4);
//starts with quarter notes, so 2 makes it eigth notes
Clock new_clock(150,16, 2);
//const char *inst = "KICK.WAV";
//Drum_channel snare("SNARE.WAV", 16);
//Drum_channel high_hat("HAT.WAV", 16);
//
//Drum_channel trial("TRIAL.WAV", 16);

void setup(){
    Serial.begin(9600);   
    AudioMemory(15);
    sgtl5000_1.enable();
    sgtl5000_1.volume(0.5);
    
    SPI.setMOSI(SDCARD_MOSI_PIN);
    SPI.setSCK(SDCARD_SCK_PIN);
    if (!(SD.begin(SDCARD_CS_PIN))) {
      while (1) {
        Serial.println("Unable to access the SD card");
        delay(500);
      }
    }
    
    new_clock.start_clock();
//    snare.set(3, 1);
//    snare.set(7, 1);  
//    snare.set(11, 1);      
//    snare.set(15, 1);
//
    kick.set(1, 1);
    kick.set(4, 1);
//    kick.set(9, 1);
    kick.set(10, 1);
    kick.set(13, 1);
    kick.set(12, 1);
//
//    high_hat.set(2, 1);
//    high_hat.set(4, 1);
//    high_hat.set(8, 1);
//    high_hat.set(10, 1);
//    playSdWav1.play(trial.getSound());
    
}

void loop() { 
    
//    
if (new_clock.change() == true) {
//        
        if (kick.On(new_clock.getStep()) == 1) {      
          kick.Trigger();
          Serial.println(new_clock.getStep());
      }
//        if (snare.On(new_clock.getStep()) == 1) {      
//          playSdWav2.play(snare.getSound());
//        
//      }
//
//        if (high_hat.On(new_clock.getStep()) == 1) {      
//          playSdWav3.play(high_hat.getSound());
//        
//      }
}
  
//
//      Serial.println(snare.On(new_clock.getStep()) == 1);
//      

//      if (kick.On(new_clock.getStep()) == 1) {      
//        playSdWav1.play(kick.getSound());
//        
//      }
//    }

}

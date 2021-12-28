#include "Sequencer.h"
#include "Drum_channel.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>
#include <math.h>



//Sequencer ins: BPM, size, note duration, num_channels, 
Sequencer sequence(200, 32, 2, 2);

//struct for Listen output
struct listen_out {
  int inst;
  int Step;
};
//starts with quarter notes, so 2 makes it eigth notes

Drum_channel kick("KICK.WAV", 16);
Drum_channel snare("SNARE.WAV", 16);
Drum_channel high_hat("HAT.WAV", 16);
//Drum_channel trial("TRIAL.WAV", 16);

int kick_arr [32] = {1,0,0,0,0,0,0,0,
                     1,0,1,0,0,0,0,0,
                     1,0,0,0,0,0,0,0,
                     1,0,0,1,0,0,0,0};
                    
int snare_arr [32] = {0,0,0,0,1,0,0,0,
                      0,0,0,0,1,0,0,1,
                      0,0,0,0,1,0,0,0,
                      0,0,0,0,1,0,1,1};
void setup(){

    Serial.begin(9600);   

                          
    kick.set_full(kick_arr);
    snare.set_full(snare_arr);
    sequence.add_instrument(&kick);
    sequence.add_instrument(&snare);
    sequence.start_clock();

    
}

void loop() { 
 
  Serial.println("here");
  delay(500);
  
}

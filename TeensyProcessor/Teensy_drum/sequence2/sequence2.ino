#include "Sequencer.h"
#include "Drum_channel.h"
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <MIDI.h>
#include <math.h>


// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav4;     //xy=147,238
AudioPlaySdWav           playSdWav3;     //xy=157,475
AudioPlaySdWav           playSdWav1;     //xy=165,133
AudioPlaySdWav           playSdWav2;     //xy=167,364
AudioMixer4              mixer3;         //xy=383,458
AudioMixer4              mixer1;         //xy=385,251
AudioMixer4              mixer2;         //xy=388,362
AudioMixer4              mixer4;         //xy=643,361
AudioOutputI2S           i2s1;           //xy=822,363
AudioConnection          patchCord1(playSdWav4, 0, mixer2, 3);
AudioConnection          patchCord2(playSdWav4, 1, mixer1, 3);
AudioConnection          patchCord3(playSdWav4, 1, mixer3, 3);
AudioConnection          patchCord4(playSdWav3, 0, mixer3, 0);
AudioConnection          patchCord5(playSdWav3, 0, mixer2, 2);
AudioConnection          patchCord6(playSdWav3, 1, mixer1, 2);
AudioConnection          patchCord7(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord8(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord9(playSdWav1, 1, mixer3, 2);
AudioConnection          patchCord10(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord11(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord12(playSdWav2, 1, mixer3, 1);
AudioConnection          patchCord13(mixer3, 0, mixer4, 2);
AudioConnection          patchCord14(mixer1, 0, mixer4, 0);
AudioConnection          patchCord15(mixer2, 0, mixer4, 1);
AudioConnection          patchCord16(mixer4, 0, i2s1, 0);
AudioConnection          patchCord17(mixer4, 0, i2s1, 1);

AudioControlSGTL5000     sgtl5000_1;     //xy=394.00000762939453,228.00003051757812

#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

//Sequencer ins: BPM, size, note duration, num_channels, 
Sequencer sequence(160, 32, 2, 2);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);
int note, velocity, channel, d1, d2;
byte type;

//struct for Listen output
struct listen_out {
  int inst;
  int Step;
};
//starts with quarter notes, so 2 makes it eigth notes

Drum_channel kick("KICK.WAV", 32);
Drum_channel snare("SNARE.WAV", 32);
Drum_channel high_hat("HAT.WAV", 32);
//Drum_channel trial("TRIAL.WAV", 16);

int kick_arr [32] = {1,0,0,0,0,0,0,0,
                     1,0,1,0,0,0,0,0,
                     1,0,0,0,0,0,0,0,
                     1,0,0,1,0,0,0,0};
                    
int snare_arr [32] = {0,0,0,0,1,0,0,0,
                      0,0,0,0,1,0,0,1,
                      0,0,0,0,1,0,0,0,
                      0,0,0,0,1,0,1,1};

//int kick_arr [32] = {0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0,
//                     0,0,0,0,0,0,0,0};
//                    
//int snare_arr [32] = {0,0,0,0,0,0,0,0,
//                      0,0,0,0,0,0,0,0,
//                      0,0,0,0,0,0,0,0,
//                      0,0,0,0,0,0,0,0};

                      
void setup(){
    MIDI.begin(MIDI_CHANNEL_OMNI);
    Serial.begin(57600);   
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



    kick.set_full(kick_arr);
    snare.set_full(snare_arr);
    sequence.add_instrument(&kick);
    sequence.add_instrument(&snare);
    sequence.start_clock();

    
}

void loop() { 

   Record(sequence);
  
}

void Play(Sequencer sequence) {
    while(true) {
      Hear();
      if (sequence.change() == true) {
      
      //go through all channels, if there is a hit, hit it 
      for (int x=0; x < sequence.getChannels(); x++) {
        if (sequence.inst_On(x)) {
          //Sort into which out source we want to use 
          if (x == 0) {playSdWav3.play(sequence.getSound(x));}
          else if (x == 1) {playSdWav4.play(sequence.getSound(x));}
//          else {playSdWav3.play(sequence.getSound(x));}
        }
      }
    }
  }
}

void parse_MIDI() {
    type = MIDI.getType();//parses first byte
    switch (type) {
      case midi::NoteOn://type=(0x90-0x9F)
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
      case midi::NoteOff:////type=(0x80-0x8F)
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
      default:
        d1 = MIDI.getData1();
        d2 = MIDI.getData2();
    } 
}

void Hear() {
    if (MIDI.read()) {
    parse_MIDI();
    if (type == midi::NoteOn) {
      playSdWav1.play(sequence.getSound(note));
      }
    }
}

listen_out Listen(Sequencer sequence) {
  listen_out out;
  listen_out null_out = {-1, -1};
  if (MIDI.read()) {
    parse_MIDI();
    if (type == midi::NoteOn) {
      playSdWav1.play(sequence.getSound(note));
      out.inst = note;
      out.Step = sequence.closest_step();
      return out;
    }

  }
  
  return null_out; 
  
}



void Record(Sequencer sequence) {
    int changeStep = -1;
    int currStep;
    listen_out _listen;
    metro(sequence);
    sequence.stop_clock();
    sequence.start_clock();
       
    while(true) {
         
        //if sequence has changed or its the first time around     
        if (sequence.change() == true) {
          currStep = sequence.getStep();
          //metronome
          if (currStep % 8 == 0) {playSdWav4.play("METRO4.WAV");}
          else if (currStep % 2 == 0) {playSdWav4.play("LOWMETRO.WAV");}
          
          Serial.println(currStep);
          for(int i=0; i<sequence.getChannels(); i++){
            if (sequence.get_instrument(i).get(currStep) == 1 && currStep != changeStep){
            playSdWav1.play(sequence.getSound(i));
            }
          } 
      }
      
      //if Listen returns a number, make that on in the
      _listen = Listen(sequence);
        
        if (_listen.inst != -1) {
          changeStep = _listen.Step;
          sequence.get_instrument(_listen.inst).set(_listen.Step, 1);          
        }
        else{if (abs(changeStep - currStep) > 2) {changeStep = -1;}}
    }
}



void metro(Sequencer sequence) {
  
    playSdWav4.play("METRO4.WAV");
    delay(sequence.getStep_interval() * 4);
  for(int x = 0; x < 3; x++) {
    playSdWav4.play("LOWMETRO.WAV");
    delay(sequence.getStep_interval() * 4);
  }
}

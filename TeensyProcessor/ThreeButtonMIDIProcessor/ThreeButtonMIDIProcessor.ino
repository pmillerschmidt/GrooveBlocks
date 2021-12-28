#include <MIDI.h>
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioPlaySdWav           playSdWav1;     //xy=165,133
AudioPlaySdWav           playSdWav2;     //xy=167,364
AudioMixer4              mixer1;         //xy=385,251
AudioMixer4              mixer2;         //xy=388,362
AudioOutputI2S           i2s1;           //xy=777,309
AudioConnection          patchCord1(playSdWav1, 0, mixer1, 0);
AudioConnection          patchCord2(playSdWav1, 1, mixer2, 0);
AudioConnection          patchCord3(playSdWav2, 0, mixer1, 1);
AudioConnection          patchCord4(playSdWav2, 1, mixer2, 1);
AudioConnection          patchCord5(mixer1, 0, i2s1, 0);
AudioConnection          patchCord6(mixer2, 0, i2s1, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=394.00000762939453,228.00003051757812

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI);


#define SDCARD_CS_PIN    10
#define SDCARD_MOSI_PIN  7
#define SDCARD_SCK_PIN   14

void setup() {
  MIDI.begin(MIDI_CHANNEL_OMNI);
  Serial.begin(57600);
  Serial.println("MIDI Input Test");

  
  AudioMemory(15);
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.7);

  SPI.setMOSI(SDCARD_MOSI_PIN);
  SPI.setSCK(SDCARD_SCK_PIN);
  if (!(SD.begin(SDCARD_CS_PIN))) {
    while (1) {
      Serial.println("Unable to access the SD card");
      delay(500);
    }
  }
}


void loop() {
  int note, velocity, channel, d1, d2;
  if (MIDI.read()) {  // Is there a MIDI message incoming ?
    byte type = MIDI.getType();//parses first byte
    switch (type) {
      case midi::NoteOn://type=(0x90-0x9F)
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        
        
        if (velocity > 0) {
          Serial.println(String("Note On:  ch=") + channel + ", note=" + note + ", velocity=" + velocity);
          if (note == 0){playSdWav1.play("KICK.WAV");}
          else if (note == 1){playSdWav2.play("SNARE.WAV");}
          else if (note == 2){playSdWav2.play("HAT.WAV");}
        } else {
          Serial.println(String("Note Off: ch=") + channel + ", note=" + note);
        }
        break;
      case midi::NoteOff:////type=(0x80-0x8F)
        note = MIDI.getData1();
        velocity = MIDI.getData2();
        channel = MIDI.getChannel();
        Serial.println(String("Note Off: ch=") + channel + ", note=" + note + ", velocity=" + velocity);
        break;
      default:
        d1 = MIDI.getData1();
        d2 = MIDI.getData2();
        Serial.println(String("Message, type=") + type + ", data = " + d1 + " " + d2);
    }
  }

}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>


//Pad Variables
int padPins[2] = {0, 1};
bool padPlaying[2] = {false, false};
int padHighscore[2] = {0, 0};
byte note[2] = {0, 0};//these numbers should be changed by rotary erncoders, these determine which note is sent in MIDI noteOn 
unsigned long timer[2] = {0, 0};
int debounce = 50;//millisecond debounce time between pad hits


int threshold = 250;//minimum value to trigger a noteSend
int sensitivity = 1000;//any analog read over 600 yields maximum velocity


//Digital Pins
int playStopButton = 12;
int recordButton = 10;
//int stopBoutton = 10;
int encoderButton1 = 2;
int encoderButton2 = 5;
int buttonPins[4] = {playStopButton, recordButton, encoderButton1, encoderButton2};
int buttonStates[4] = {0, 0, 0, 0};
int lastButtonStates[4] = {0, 0, 0, 0};

Encoder knob1(4, 3);
Encoder knob2(6, 7);
int pos1 = 0;
int pos2 = 0;
int old_pos1 = -1;
int old_pos2 = -1;

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_RESET);

void setup() {
  Serial.begin(9600);
  //OLED Setup
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);    

  //Buttons Settup
  pinMode(encoderButton1, INPUT);
  pinMode(encoderButton2, INPUT);
  pinMode(playStopButton, INPUT);
  pinMode(recordButton, INPUT);

  
}

void noteOn(int cmd, int pitch, int velocity) {//scale velocity here
  if (velocity > sensitivity) velocity = sensitivity;
  float scaledVelocity = (velocity / float(1000)) * 127;
  Serial.println("new noteOn. Velocity:");
  Serial.println((int)scaledVelocity);
  //Serial.write(cmd);
  //Serial.write(pitch);
  //Serial.write(scaledVelocity);
}

void noteOff(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

/*
 * This method checks to see if current input is th largest input in a particular pad hit
 */
void playNote(int pad, int padVelocity){
  if (padVelocity > padHighscore[pad]){//temp change
    padHighscore[pad] = padVelocity;
  }
}


void scanPads(){
  for(int i = 0; i < 1; i++){
      int padVelocity = analogRead(padPins[i]);
      if (padVelocity >= threshold && padPlaying[i] == false){//highest score handled in playNote()
        if ((millis() - timer[i]) >= debounce){//debounce is time between possibly played notes
          padPlaying[i] = true;
          playNote(i, padVelocity);//this method doesn't send midi, it keeps track of highscore
          Serial.println("case1");
        }        
      }
      else if (padVelocity >= threshold && padPlaying[i] == true){
        playNote(i, padVelocity);//doesn't so anything unless, this padVelocity is the peak
        Serial.println("case2");

      }
      else if (padVelocity < threshold && padPlaying[i] == true){//end of the spike
        //send Midi events
        Serial.print("case3, highscore =");
        Serial.println(padHighscore[i]);
        noteOn(0x90, note[i], padHighscore[i]);
        padHighscore[i] = 0;
        padPlaying[i] = false;
        timer[i] = millis();
      }
  }
}

void updateDisplay(int pos) {
  display.clearDisplay();
  display.setCursor(0,0);
  display.print(pos);
  display.display();
}


void scanRotaryEncoders(){
    //rotary encoders
  int knob_read1;
  int knob_read2;
  knob_read1 = knob1.read();  
  knob_read2 = knob2.read();  
  pos1 = (knob_read1 / 10);
  pos2 = (knob_read2 / 10);
  //checking knobs
  if (pos1 != old_pos1) {
    updateDisplay(pos1);
    old_pos1 = pos1;
  }
  if (pos2 != old_pos2) {
    updateDisplay(pos2);
    old_pos2 = pos2;
  }
}

//The following three mthods are used in the scanButtons loop
void noteChange(int posNumber, int encoder){
  Serial.print("note changed from ");
  Serial.print(note[encoder]);
  Serial.print("to");
  Serial.print(posNumber);
  note[encoder] = posNumber;
  
}

void playStop(){
  //send some MIDI message to play
  Serial.println("play/stop");
}
void record(){
  //Send MIDI message to start recording
  Serial.println("recording");
}

void scanButtons(){
  for (int i = 0; i < 4; i = i + 1) {//because there are 4 buttons right now
    buttonStates[i] = digitalRead(buttonPins[i]);
  }
  if (buttonStates[0] != lastButtonStates[0] && buttonStates[0] == LOW){
    playStop();
    delay(50);
  }
  if (buttonStates[1] != lastButtonStates[1] && buttonStates[1] == LOW){
    record();
    delay(50);
  }
  if (buttonStates[2] != lastButtonStates[2] && buttonStates[2] == LOW){
    noteChange(pos1, 0);
  }
  if (buttonStates[3] != lastButtonStates[3] && buttonStates[3] == LOW){
    noteChange(pos2, 1);  
  }

  for (int i = 0; i < 4; i = i + 1) {//because there are 4 buttons right now
    lastButtonStates[i] = buttonStates[i];
  }

}



void loop() {
  //pads
  scanPads();
  scanRotaryEncoders();
  scanButtons();
  
}

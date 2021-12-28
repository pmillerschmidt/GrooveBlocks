
int buttonPins[3] = {12, 11, 10};//button1,2,3 


int buttonStates[3] = {0, 0, 0};         // current state of the button
int lastButtonStates[3] = {0, 0, 0}; 


void setup() {
  // initialize the pushbutton pin as an input:
  for (int i = 0; i < 3; i = i + 1) {//3 because there are 3 buttons
    pinMode(buttonPins[i], INPUT);
  }
  
  Serial.begin(31250);
}

void loop() {
 // read the pushbutton input pin:
  for (int i = 0; i < 3; i = i + 1) {
    buttonStates[i] = digitalRead(buttonPins[i]);
    // compare the buttonState to its previous state
    if (buttonStates[i] != lastButtonStates[i] && buttonStates[i] == HIGH) {// if the current state is HIGH then the button went from off to on:     
      noteOn(0x90, i, 0x45);
      // Delay a little bit to avoid bouncing
      delay(50);
    }else if(buttonStates[i] != lastButtonStates[i] && buttonStates[i] == LOW){
    // save the current state as the last state, for next time through the loop
    noteOff(0x80, i, 0x45);
      delay(50);
    }
    lastButtonStates[i] = buttonStates[i];
  }
}



void noteOn(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

void noteOff(int cmd, int pitch, int velocity) {
  Serial.write(cmd);
  Serial.write(pitch);
  Serial.write(velocity);
}

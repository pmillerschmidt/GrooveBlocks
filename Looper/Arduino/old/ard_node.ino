

int MIDIpin = A0;
int effectPin = A1;
int instPin = A2;

//initialize the vars to be sent 
int MIDI = 0;
int effect = 0;
int inst = 0;

//old vals
int last_MIDI = 0;
int last_effect = 0;
int last_inst = 0;

void setup() {
  // declare the ledPin as an OUTPUT:


  
  Serial.begin(9600);



}

void loop() {
        
  
  //update last values
  last_MIDI = MIDI;
  last_effect = effect;
  last_inst = inst;
  
  // read the values from the nodes
  MIDI = analogRead(MIDIpin);
  effect = analogRead(effectPin);
  inst = analogRead(instPin);
  
  
  //if there is a difference then update the Serial
//  if (difVals(last_MIDI, MIDI) || difVals(last_effect, effect) || difVals(last_inst, inst)) {
    String divider = ":";
  Serial.print(MIDI + divider + effect + divider + inst + divider);
  delay(250);
  

  
}

bool difVals(int first, int second) {
  
  if (first == second) {return false;}
  
  //what's the threshhold? start with 20
  if (abs(first - second) > 20) {
    //Serial.println((abs(first - second) / first));
    return true;
  } else {return false;}
}

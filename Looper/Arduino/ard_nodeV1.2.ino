#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

//set up neopixel
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      2

//set up slave address 
#define SLAVE_ADDRESS 0x04
int number = 0;
int state = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


int delayval = 500; // delay for half a second

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

//vibration sensor
int vib = 4;

void setup() {
  // declare the ledPin as an OUTPUT:

  pinMode(vib, OUTPUT);
  
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.clear();

  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);
    
  // define callbacks for i2c communication
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
    
  Serial.println("Ready!");

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
//    flash();
//    vibrate();
//    flash();
//    vibrate();
//    Serial.print("change");
// }
//    
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

void flash() {
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(0, pixels.Color(200, 0,100)); // Moderately bright green color.
    pixels.setPixelColor(1, pixels.Color(200, 0,100)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(50); // Delay for a period of time (in milliseconds).
    pixels.setPixelColor(0, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.setPixelColor(1, pixels.Color(0,0,0)); // Moderately bright green color.
    pixels.show(); // This sends the updated pixel color to the hardware.
}

void vibrate() {
  digitalWrite(vib, HIGH);
  delay(200);
  digitalWrite(vib,LOW);
}


// callback for received data
void receiveData(int byteCount){

  while(Wire.available()) {
    number = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);

   if (number == 1){

      if (state == 0){
         digitalWrite(13, HIGH); // set the LED on
         state = 1;
     }
   else{
      digitalWrite(13, LOW); // set the LED off
      state = 0;
     }
    }
  }
} 

// callback for sending data
void sendData(){
  Wire.write(MIDI);
}



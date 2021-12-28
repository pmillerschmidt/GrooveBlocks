#include <Wire.h>

#define SLAVE_ADDRESS 0x04

volatile boolean receiveFlag = false;
char temp[32];
String command;

void setup() {
  // initialize i2c as slave
  Wire.begin(SLAVE_ADDRESS);

  // define callbacks for i2c communication
  Wire.onReceive(receiveEvent);

  Serial.begin(9600);
  Serial.println("Ready!");

}

void loop() {
  delay(1000);
  if (receiveFlag == true) {
    Serial.println("inFlag");
    Serial.println(command);
    receiveFlag = false;
  }
}

void receiveEvent(int howMany) {
  //works as expected
  /*while (0 < Wire.available()) { // loop through all
    char c = Wire.read();
    Serial.print(c);
    }*/

  int count = 0;
  while (0 < Wire.available()) { // loop through all
    temp[count] = Wire.read();
    count++;
  }
  //temp[32-1]='\0'; //make sure its 0 terminated, didn't matter
  command = temp; //put char array into a string variable named command

  Serial.print(temp); // prints nothing....

  //Verify Array is Loaded..works great.
  //for (int i = 0; i < count; i++)
  //{
  //  Serial.println(temp[i]);
  //}
  receiveFlag = true;
}
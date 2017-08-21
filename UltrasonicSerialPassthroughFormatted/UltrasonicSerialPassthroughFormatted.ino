/*****************************************************************
  UltrasonicSerialPassthroughFormatted.ino

  Set up a software serial port to pass data between an ultrasonic
  range finder and the serial monitor.

  Hardware Hookup:

  Ultrasonic Range Finder - Redboard
  GND - GND
  Vcc - 5V
  Tx - Pin 2 (software serial rx)
  
*****************************************************************/
// We'll use SoftwareSerial to communicate with the ultrasonic:
#include <SoftwareSerial.h>
// ultrasonic's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// ultrasonic's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial ultrasonic(2, 3, true); // RX, TX, inverse_logic = true

char c;

void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the ultrasonic. Make sure the baud rate matches the config
  // setting of your ultrasonic range finder.
  ultrasonic.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available())  { // If data comes in from serial monitor, send it out to ultrasonic
    ultrasonic.write(Serial.read());
  }
  if (ultrasonic.available()) { // If data comes in from ultrasonic, send it out to serial monitor
    c = ultrasonic.read();//take char out of buffer and place in variable
    if (c == 13) {//if there is a carriage return (ASCII 13) print on next line
      Serial.println();
    }
    else if (c == 82) { //if there is an R (ASCII 82), don't print
    }
    else {
      Serial.write(c);//print data
    }
  }

}//end loop

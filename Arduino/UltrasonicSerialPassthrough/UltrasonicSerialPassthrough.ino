/*****************************************************************
 * UltrasonicSerialPassthrough.ino
 * By: Ho Yun "Bobby" Chan @ SparkFun Electronics Inc.
 * Date: August 22, 2017
 * 
 * Description: Set up a software serial port to pass data between an ultrasonic
 * range finder and the serial monitor. The data is inverted.
 *
 * Hardware Hookup:
 *
 * Ultrasonic Range Finder - Redboard
 * GND - GND
 * Vcc - 5V
 * Tx - Pin 2 (software serial rx)
 *
 * This code is released under the [MIT License](http://opensource.org/licenses/MIT).
 * Please review the LICENSE.md file included with this example. 
 *
 *****************************************************************/
// We'll use SoftwareSerial to communicate with the ultrasonic:
#include <SoftwareSerial.h>
// ultrasonic's TX is connected to pin 2 (Arduino's Software RX)
// ultrasonic's RX is connected to pin 3 (Arduino's Software TX)
SoftwareSerial ultrasonic(2, 3, true); // RX, TX, inverse_logic = true

void setup() {
  // Set up both ports at 9600 baud. This value is most important
  // for the ultrasonic sensor. Make sure the baud rate matches the
  // config setting of your ultrasonic range finder.
  ultrasonic.begin(9600);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) { // If data comes in from serial monitor, send it out to ultrasonic
    ultrasonic.write(Serial.read());
  }
  if (ultrasonic.available()) { // If data comes in from ultrasonic, send it out to serial monitor
    Serial.write(ultrasonic.read());//print data
  }

}//end loop

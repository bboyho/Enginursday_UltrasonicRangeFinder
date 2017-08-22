/*****************************************************************
  UltrasonicASCIItoDecimal.ino
  By: Ho Yun "Bobby" Chan @ SparkFun Electronics Inc.

  Set up a software serial port to pass data between an ultrasonic
  range finder and the serial monitor. Store incoming values into
  array and convert values to decimal. The array is also used to 
  verify the final range.

  Hardware Hookup:

  Ultrasonic Range Finder - Redboard
  GND - GND
  Vcc - 5V
  Tx - Pin 2 (software serial rx)

*****************************************************************/
// We'll use SoftwareSerial to communicate with the ultrasonic:
#include <SoftwareSerial.h>
// ultrasonic's TX is connected to pin 2 (Arduino's Software RX)
// ultrasonic's RX is connected to pin 3 (Arduino's Software TX)
SoftwareSerial ultrasonic(2, 3, true); // RX, TX, inverse_logic = true

char c;//var to save incoming data
char range[6]; //array to store data for sensor (i.e. range[6] = {'R','0','1','6','\r','\0'} )
int index = 0;//to keep track of location in array
int temp_sum = 0;//temp value to keep track of sum
int sum = 0;//final range

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
    c = ultrasonic.read();//take ASCII out of buffer and place in variable

    if (c == 82) {//if there is an R (ASCII 82), don't print
      range[0] = 'R';
      index = 3;//number of digits left to read
    }
    else if (c == 13) { //if there is a carriage return (ASCII 13) print on next line
      Serial.print("range = ");//print range
      Serial.println(temp_sum);
      //Serial.println();

      range[4] = '\r';

      //print array to verify final range
      for (int i = 0; i < 5; i++) {
        //Serial.print("range[] = ");
        Serial.print(range[i]);
      }
      Serial.println();
    }

    else {//convert read range from ASCII to decimal here
      if (index == 3) {
        sum = 0;
        temp_sum = 0;

        range[1] = c;
        temp_sum  = (temp_sum + (c - 48) * 100); //hundredths place
      }
      else if (index == 2) {
        range[2] = c;
        temp_sum  = (temp_sum + (c - 48) * 10); //tens place
      }
      else if (index == 1) {
        range[3] = c;
        temp_sum  = temp_sum + (c - 48); //ones place
      }

      sum = temp_sum; //add value to final range
      index = index - 1; //decrement by 1 and save to index
    }
  }

}//end loop

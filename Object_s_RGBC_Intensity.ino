/*
 * @author REHAN JAVED
 * @company RJ APPS
 * @website http://www.rehanjaved.com
 * @version 1.0
 * @date 26th April 2017
 * 
 * When any object is placed near to
 * the RGB Color Sensor TCS3200 this
 * code will get the intensity of
 * RED, GREEN, BLUE and CLEAR photodiode
 * intensity of that object.
 * Data printed to the Serial Monitor.
 * 
 * OUT wire of sensor connected at DIGITAL 2 port.
 * S3 wire of sensor connected at DIGITAL 3 port.
 * S2 wire of sensor connected at DIGITAL 4 port.
 * S1 wire of sensor connected at DIGITAL 5 port.
 * S0 wire of sensor connected at DIGITAL 6 port.
 * VCC wire of sensor connected at 5V in Uno.
 * GND wire of sensor connected at GND in Uno.
 * E0 wire of sensor connected at GND in Uno.
 * 
 * Device => ARDUINO UNO R3
 *
 */

// To get frequency of object.
unsigned int RED = 0;
unsigned int GREEN = 0;
unsigned int BLUE = 0;
unsigned int CLEAR = 0;
// Sensor Wires connected to Digital Input/Output ports.
#define OUT 2
#define S3 3
#define S2 4
#define S1 5
#define S0 6
// text contained to put on the console
// at the end of the loop.
String consoleOutput = "";

void setup() {
  
  Serial.begin(9600);

  // To get the specific 
  // color frequency.
  // S3  S2  Photodiode Type
  // L   L   RED
  // L   H   BLUE
  // H   L   CLEAR
  // H   H   GREEN
  pinMode(S3, OUTPUT);
  pinMode(S2, OUTPUT);

  // To set the output frequency scaling
  // S0  S1  FREQUENCY
  // L   L   Power Down
  // L   H   2%
  // H   L   20%
  // H   H   100%
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);

  // To get the pulse in/frequency of 
  // the color in the object placed
  // in front of it.
  pinMode(OUT, INPUT);

  // Setting the output frequency scaling
  // to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

}

// the loop function runs over and over again forever
void loop() {

  RED = getColorFrequency(LOW, LOW); // frequency of red color.
  GREEN = getColorFrequency(HIGH, HIGH); // frequency of green color.
  BLUE = getColorFrequency(LOW, HIGH); // frequency of blue color.
  CLEAR = getColorFrequency(HIGH, LOW); // frequency of clear.

  // Making the ouput for console.
  consoleOutput = consoleOutput + "Red: " + RED;
  consoleOutput = consoleOutput + ", Green: " + GREEN;
  consoleOutput = consoleOutput + ", Blue: " + BLUE;
  consoleOutput = consoleOutput + ", Clear: " + CLEAR;
  
  // printing to console.
  Serial.println(consoleOutput);
  consoleOutput = "";

  // delaying the program to 1 second.
  delay(400);

}

// Take S3 and S2 digital value
// and return the frequency of
// the specific color taken by
// S3 and S2 gate match.
int getColorFrequency(uint8_t _s3, uint8_t _s2){

  // setting S3 and S2 digital signal.
  digitalWrite(S3, _s3);
  digitalWrite(S2, _s2);
  // returning the frequency of that color.
  return pulseIn(OUT, LOW);
  
}



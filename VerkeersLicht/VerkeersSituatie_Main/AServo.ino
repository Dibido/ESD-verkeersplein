#include <Servo.h>
//Set servo PIN
const unsigned char POORTPIN = 9;
const unsigned char SERVOBUTTONPIN = 2;
//Create servo object.
Servo poort;
//Variable to store servo position
unsigned char servoPos = 0;

void servo_Setup(void) {
  poort.attach(POORTPIN);
  poort.write(servoPos);
}

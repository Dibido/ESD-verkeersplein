//Pin definition of Arduino connected to pins Shift Register.
const unsigned char DATASERIAL = 5; // connected to pin 14 Shift Register
const unsigned char STORAGE = 6;    // connected to pin 12 Shift Register
const unsigned char CLOCK = 7;     // connected to pin 11 Shift Register
//Pattern definitions.
const unsigned char NUMBEROFSYMBOLS = 3;
const unsigned char NUMBEROFNUMBERS= 7;
const unsigned char NUMBEROFLEDS = 8;
//Array of symbols used
const byte LEDSYMBOLS [NUMBEROFSYMBOLS] =
{
  B11100110,//S
  B11110110,//g
  B10010111,//d
};
//Array of numbers used
const byte LEDNUMBERS [NUMBEROFNUMBERS] =
{
  B11110111,//0
  B01000001,//1
  B10110011,//2
  B10110110,//3
  B11010100,//4
  B11100110,//5
  B11100111,//6
};

void display_Setup() {
  //Initialize pins as output.
  pinMode(STORAGE, OUTPUT);
  pinMode(DATASERIAL, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  //Initialize pins to be LOW.
  digitalWrite(DATASERIAL, LOW);
  digitalWrite(CLOCK, LOW);
  digitalWrite(STORAGE, LOW);
}

// Shift one bit.
void bitShift(boolean OnOff) {
  digitalWrite(DATASERIAL, OnOff);
  digitalWrite(CLOCK, HIGH);
  digitalWrite(CLOCK, LOW);
}

//Check wether a bit in a pattern is set.
boolean isSet(byte pattern, byte bitnr) {
  bitnr = 1 << bitnr;
  if ((pattern & bitnr) != 0) return true;
  else return false;
}

//Set a byte pattern
void displaySetLed8Bit(byte bitpattern) {
  digitalWrite(STORAGE, LOW);
  shiftOut(DATASERIAL, CLOCK, MSBFIRST, bitpattern);
  digitalWrite(STORAGE, HIGH);
}

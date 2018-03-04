const unsigned char AANTAL_VERKEERSLICHTEN = 2;
const unsigned char AANTAL_LAMPEN = 3;
//PinArray of the lights
const unsigned char STOPLICHTEN_PINS[AANTAL_VERKEERSLICHTEN][AANTAL_LAMPEN] = {
  {2, 3, 4},
  {13, 12, 11},
};

void led_Setup(){
  //Set All pins to output.
  for (int i = 0; i < AANTAL_VERKEERSLICHTEN; i++) {
    for (int j = 0; j < AANTAL_LAMPEN; j++) {
      pinMode(STOPLICHTEN_PINS[i][j], OUTPUT);
    }
  }
}

//Turns a light on
void StopLichtLampAan(unsigned char stoplicht, unsigned char pin){
  digitalWrite(STOPLICHTEN_PINS[stoplicht][pin], HIGH);
}

//Turns a light off
void StopLichtLampUit(unsigned char stoplicht, unsigned char pin){
  digitalWrite(STOPLICHTEN_PINS[stoplicht][pin], LOW);
}

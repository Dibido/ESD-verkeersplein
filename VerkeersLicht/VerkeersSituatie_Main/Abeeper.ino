//Set beeper pin
const unsigned char BEEPERPIN = 10;

void beeper_Setup(void){
  pinMode(BEEPERPIN, OUTPUT);
}

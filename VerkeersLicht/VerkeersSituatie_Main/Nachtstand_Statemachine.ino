//Module Nachtstand

//States
const unsigned char NACHTSTAND_LICHT = 1;
const unsigned char NACHTSTAND_DONKER = 2;

//Limits to change state
const unsigned int LICHT_LIMIT = 400;
const unsigned int DONKER_LIMIT = 1000;

//Speed to blink at
const unsigned char knipperSnelheid = 250;

//Current State
unsigned char nachtstand_State;
boolean geelState;

//Timer
unsigned long knipperTimer;


void nachtstand_Setup() {
  nachtstand_State = NACHTSTAND_LICHT;
  nachtstand_Licht_Entry();
}

void nachtstand_Loop() {
  Serial.print("LDR :");
  Serial.println(readLDR());
  Serial.print("State :");
  Serial.println(nachtstand_State);
  Serial.print("Poort :");
  switch (nachtstand_State) {
    case NACHTSTAND_LICHT:
      nachtstand_Licht_Do();
      if (readLDR() > DONKER_LIMIT) {
        nachtstand_Licht_Exit();
        nachtstand_State = NACHTSTAND_DONKER;
        nachtstand_Donker_Entry();
      }
      break;
    case NACHTSTAND_DONKER:
      nachtstand_Donker_Do();
      if (readLDR() < LICHT_LIMIT) {
        nachtstand_Donker_Exit();
        nachtstand_State = NACHTSTAND_LICHT;
        nachtstand_Licht_Entry();
      }
      break;
  }
}

// --- NACHTSTAND_LICHT -----------
void nachtstand_Licht_Entry() {
  toonStoppen();
  for (int i = 0; i < AANTAL_VERKEERSLICHTEN; i++) {
    StopLichtLampUit(i, 1);
    StopLichtLampAan(i, 2);
  }
  while(poort.read() > 0){
    sluitPoort();
  }
}
void nachtstand_Licht_Do(){
  //<nothing>
}
void nachtstand_Licht_Exit() {
  //<nothing>
}
// --- NACHTSTAND_DONKER -----------
void nachtstand_Donker_Entry() {
  knipperTimer = millis();
  geelState = LOW;
  toonDanger();
  for (int i = 0; i < AANTAL_VERKEERSLICHTEN; i++) {
    StopLichtLampUit(i, 2);
  }
}
void nachtstand_Donker_Do() {
  openPoort();
  knipperGeel();
}
void nachtstand_Donker_Exit() {
  for (int i = 0; i < AANTAL_VERKEERSLICHTEN; i++) {
    StopLichtLampAan(i, 1);
  }
}

//Functies
void toonDanger() {
  displaySetLed8Bit(LEDSYMBOLS[2]);
}

void knipperGeel() {
  if (isTimeElapsed(knipperSnelheid, knipperTimer)) {
    if (geelState == LOW) {
      knipperTimer = millis();
      geelState = HIGH;
      for (int i = 0; i < 2; i++) {
        StopLichtLampAan(HIGH, 1);
      }
    }
    else {
      knipperTimer = millis();
      geelState = LOW;
      for (int i = 0; i < 2; i++) {
        StopLichtLampUit(i, 1);
      }
    }
  }
}


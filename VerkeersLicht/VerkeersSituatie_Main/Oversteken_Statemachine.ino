//Module Oversteken

//States
const unsigned char OVERSTEKEN_STOPPEN = 1;
const unsigned char OVERSTEKEN_GAAN = 2;
const unsigned char OVERSTEKEN_AFTELLEN = 3;

//State times
const unsigned int GAANTIJD = 1000;
const unsigned int AFTELLENTIJD = 10000;

//Current state
unsigned char oversteken_State;

//Current displayvalue
unsigned char display_State;

//Delays
const unsigned int DISPLAYAFTELLENDELAY = 1400;
const unsigned char TIKAFTELLENTUSSENDELAY = 200;
const unsigned int TIKAFTELLENNADELAY = 1000;

//Timer
unsigned long overstekenPreviousMillis;
unsigned long tikkenPreviousMillis;
unsigned long aftellenDisplayPreviousMillis;
unsigned long aftellenBuzzerPreviousMillis;

//Tellers
unsigned char buzzerTikTeller;


void oversteken_Setup() {
  oversteken_State = OVERSTEKEN_STOPPEN;
  oversteken_Stoppen_Entry();
}

void oversteken_Loop() {
  switch (oversteken_State) {
    case OVERSTEKEN_STOPPEN:
      oversteken_Stoppen_do();
      if (buttonPressed(SERVOBUTTONPIN) && alleLichtenStoppen()) {
        oversteken_Stoppen_Exit();
        oversteken_State = OVERSTEKEN_GAAN;
        oversteken_Gaan_Entry();
      }
      break;
    case OVERSTEKEN_GAAN:
      oversteken_Gaan_do();
      if (isTimeElapsed(GAANTIJD, overstekenPreviousMillis)) {
        oversteken_Gaan_Exit();
        oversteken_State = OVERSTEKEN_AFTELLEN;
        oversteken_Aftellen_Entry();
      }
      break;
    case OVERSTEKEN_AFTELLEN:
      oversteken_Aftellen_do();
      if (isTimeElapsed(AFTELLENTIJD, overstekenPreviousMillis)) {
        oversteken_Aftellen_Exit();
        oversteken_State = OVERSTEKEN_STOPPEN;
        oversteken_Stoppen_Entry();
      }
      break;
  }
}


// --- OVERSTEKEN_STOPPEN -----------
void oversteken_Stoppen_Entry() {
  toonStoppen();
}
void oversteken_Stoppen_do() {
  if(nachtstand_State != NACHTSTAND_DONKER){
  tikStoppen();
  }
}
void oversteken_Stoppen_Exit() {
  // <nothing>
}
// --- OVERSTEKEN_GAAN -----------
void oversteken_Gaan_Entry() {
  overstekenPreviousMillis = millis();
  toonGaan();
}
void oversteken_Gaan_do() {
  tikGaan();
}
void oversteken_Gaan_Exit() {
  //<nothing>
}
// --- OVERSTEKEN_AFTELLEN -----------
void oversteken_Aftellen_Entry() {
  overstekenPreviousMillis = millis();
  display_State = NUMBEROFNUMBERS - 1;
  buzzerTikTeller = 0;
}
void oversteken_Aftellen_do() {
  displayAftellen();
  tikAftellen();
}
void oversteken_Aftellen_Exit() {
  // <nothing>
}

//Functions

//Display:
void toonStoppen() {
  displaySetLed8Bit(LEDSYMBOLS[0]);
}

void toonGaan() {
  displaySetLed8Bit(LEDSYMBOLS[1]);
}
void displayAftellen() {
  if (isTimeElapsed(DISPLAYAFTELLENDELAY, aftellenDisplayPreviousMillis)) {
    aftellenDisplayPreviousMillis = millis();
    displaySetLed8Bit(LEDNUMBERS[display_State]);
    display_State--;
  }
}

//Beeper:

void tikStoppen() {
  if (isTimeElapsed(500, tikkenPreviousMillis)) {
    tikkenPreviousMillis = millis();
    tone(BEEPERPIN, 250, 2);
  }
}

void tikGaan() {
  if (isTimeElapsed(200, tikkenPreviousMillis)) {
    tikkenPreviousMillis = millis();
    tone(BEEPERPIN, 250, 2);
  }
}

void tikAftellen() {
  if (isTimeElapsed(TIKAFTELLENTUSSENDELAY, aftellenBuzzerPreviousMillis) && buzzerTikTeller < 3) {
    aftellenBuzzerPreviousMillis = millis();
    tone(BEEPERPIN, 250, 2);
    buzzerTikTeller++;
  }
  else if (isTimeElapsed(TIKAFTELLENNADELAY, aftellenBuzzerPreviousMillis)) {
    aftellenBuzzerPreviousMillis = millis();
    buzzerTikTeller = 0;
  }
}

// Module verkeersLicht

// --- States -----------
const unsigned char VERKEERSLICHT_STOPPEN = 1;
const unsigned char VERKEERSLICHT_RIJDEN = 2;
const unsigned char VERKEERSLICHT_AFREMMEN = 3;
const unsigned char VERKEERSLICHT_UITLOPEN = 4;

//--- Lampen -------------
const unsigned char GROEN = 0;
const unsigned char GEEL = 1;
const unsigned char ROOD = 2;

//Time for each state
const unsigned int RIJDENTIJD = 2000;
const unsigned int AFREMMENTIJD = 500;
const unsigned int UITLOPENTIJD = 1000;

// Current state
unsigned char verkeersLicht_States[AANTAL_VERKEERSLICHTEN];

// Timers
unsigned long verkeerslichtpreviousMillis[AANTAL_VERKEERSLICHTEN];

// --- Setup -------------------
void verkeersLicht_Setup() {
  // Start state
  for (int i = 0; i < AANTAL_VERKEERSLICHTEN; i++) {
    verkeersLicht_States[i] = VERKEERSLICHT_STOPPEN;
    verkeersLicht_Stoppen_Entry(i);
  }
}

// --- Loop --------------------
void verkeersLicht_Loop() {
  for (int verkeerslichtNR = 0; verkeerslichtNR < AANTAL_VERKEERSLICHTEN; verkeerslichtNR++) {
    switch (verkeersLicht_States[verkeerslichtNR]) {
      case VERKEERSLICHT_STOPPEN:
        verkeersLicht_Stoppen_Do();
        if (buttonPressed(verkeerslichtNR) && poortGesloten() && alleLichtenStoppen()) {
          verkeersLicht_Stoppen_Exit(verkeerslichtNR);
          verkeersLicht_States[verkeerslichtNR] = VERKEERSLICHT_RIJDEN;
          verkeersLicht_Rijden_Entry(verkeerslichtNR);
        }
        break;
      case VERKEERSLICHT_RIJDEN:
        verkeersLicht_Rijden_Do();
        if (isTimeElapsed(RIJDENTIJD, verkeerslichtpreviousMillis[verkeerslichtNR])) {
          verkeersLicht_Rijden_Exit(verkeerslichtNR);
          verkeersLicht_States[verkeerslichtNR] = VERKEERSLICHT_AFREMMEN;
          verkeersLicht_Afremmen_Entry(verkeerslichtNR);
        }
        break;
      case VERKEERSLICHT_AFREMMEN:
        verkeersLicht_Afremmen_Do();
        if (isTimeElapsed(AFREMMENTIJD, verkeerslichtpreviousMillis[verkeerslichtNR])) {
          verkeersLicht_Afremmen_Exit(verkeerslichtNR);
          verkeersLicht_States[verkeerslichtNR] = VERKEERSLICHT_UITLOPEN;
          verkeersLicht_Uitlopen_Entry(verkeerslichtNR);
        }
        break;
      case VERKEERSLICHT_UITLOPEN:
        verkeersLicht_Uitlopen_Do();
        if (isTimeElapsed(UITLOPENTIJD, verkeerslichtpreviousMillis[verkeerslichtNR])) {
          verkeersLicht_Uitlopen_Exit(verkeerslichtNR);
          verkeersLicht_States[verkeerslichtNR] = VERKEERSLICHT_STOPPEN;
          verkeersLicht_Stoppen_Entry(verkeerslichtNR);
        }
        break;
    }
  }
}

// --- VERKEERSLICHT_STOPPEN -----------
void verkeersLicht_Stoppen_Entry(unsigned char stoplicht) {
  StopLichtLampAan(stoplicht, ROOD);
  button_switch_States[stoplicht] = false;
}

void verkeersLicht_Stoppen_Do() {
  // <nothing>
}

void verkeersLicht_Stoppen_Exit(unsigned char stoplicht) {
  StopLichtLampUit(stoplicht, ROOD);
}

// --- VERKEERSLICHT_RIJDEN -----------
void verkeersLicht_Rijden_Entry(unsigned char stoplicht) {
  StopLichtLampAan(stoplicht, GROEN);
  verkeerslichtpreviousMillis[stoplicht] = millis();
}

void verkeersLicht_Rijden_Do() {
  // <nothing>
}

void verkeersLicht_Rijden_Exit(unsigned char stoplicht) {
  StopLichtLampUit(stoplicht, GROEN);
}

// --- VERKEERSLICHT_AFREMMEN -----------
void verkeersLicht_Afremmen_Entry(unsigned char stoplicht) {
  StopLichtLampAan(stoplicht, GEEL);
  verkeerslichtpreviousMillis[stoplicht] = millis();
}

void verkeersLicht_Afremmen_Do() {
  // <nothing>
}

void verkeersLicht_Afremmen_Exit(unsigned char stoplicht) {
  StopLichtLampUit(stoplicht, GEEL);
}

// --- VERKEERSLICHT_UITLOPEN -----------
void verkeersLicht_Uitlopen_Entry(unsigned char stoplicht) {
  verkeerslichtpreviousMillis[stoplicht] = millis();
  StopLichtLampAan(stoplicht, ROOD);
}

void verkeersLicht_Uitlopen_Do() {
  // <nothing>
}

void verkeersLicht_Uitlopen_Exit(unsigned char stoplicht) {
  StopLichtLampUit(stoplicht, ROOD);
}

//Functions
//functie die checkt of alle stoplichten op stoppen staan.
boolean alleLichtenStoppen(){
  boolean allStoppen = true;
  for(int i = 0; i < AANTAL_VERKEERSLICHTEN; i++){
    if(verkeersLicht_States[i] != VERKEERSLICHT_STOPPEN){
      allStoppen = false;
    }
  }
  return allStoppen;
}

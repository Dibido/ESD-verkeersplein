//Module Poort

//States
const unsigned char POORT_GESLOTEN = 1;
const unsigned char POORT_OPENEN = 2;
const unsigned char POORT_OPEN = 3;
const unsigned char POORT_SLUITEN = 4;

//Standen
const unsigned char GESLOTEN = 0;
const unsigned char GEOPEND = 90;

//Tijd om de poort geopend te hebben.
const unsigned int TIJDGEOPEND = 10000;

//Servo beweging instellingen
const int BEWEEGTIJD = 50;
const unsigned char BEWEEGSNELHEID = 1;
//Timer voor het bewegen
unsigned long poortBeweegTimer;

//Current state
unsigned char poort_State;

//Timer om de poort open te houden
unsigned long poortPreviousMillis;

//Setup
void poort_Setup() {
  // Start state
  poort_State = POORT_GESLOTEN;
  poort_Gesloten_Entry();
}

void poort_Loop() {
  switch (poort_State) {
    case POORT_GESLOTEN:
      poort_Gesloten_Do();
      if (buttonPressed(SERVOBUTTONPIN) && alleLichtenStoppen()) {
        poort_Gesloten_Exit();
        poort_State = POORT_OPENEN;
        poort_Openen_Entry();
      }
      break;
    case POORT_OPENEN:
      poort_Openen_Do();
      if (poort.read() == GEOPEND) {
        poort_Openen_Exit();
        poort_State = POORT_OPEN;
        poort_Open_Entry();
      }
      break;
    case POORT_OPEN:
      poort_Open_Do();
      if (isTimeElapsed(TIJDGEOPEND, poortPreviousMillis)) {
        poort_Open_Exit();
        poort_State = POORT_SLUITEN;
        Poort_Sluiten_Entry();
      }
      break;
    case POORT_SLUITEN:
      poort_Sluiten_Do();
      if (poort.read() == GESLOTEN) {
        poort_Sluiten_Exit();
        poort_State = POORT_GESLOTEN;
        poort_Gesloten_Entry();
      }
      break;
  }
}

// --- POORT_GESLOTEN -----------
void poort_Gesloten_Entry() {
  button_switch_States[SERVOBUTTONPIN] = false;
}
void poort_Gesloten_Do() {
  // <nothing>
}
void poort_Gesloten_Exit() {
  // <nothing>
}
// --- POORT_OPENEN -----------
void poort_Openen_Entry() {
  openPoort();
}
void poort_Openen_Do() {
  // <nothing>
}
void poort_Openen_Exit() {
  // <nothing>
}
// --- POORT_OPEN -----------
void poort_Open_Entry() {
  poortPreviousMillis = millis();
}
void poort_Open_Do() {
  // <nothing>
}
void poort_Open_Exit() {
  // <nothing>
}
// --- POORT_SLUITEN -----------
void Poort_Sluiten_Entry() {
  sluitPoort();
}
void poort_Sluiten_Do() {
  // <nothing>
}
void poort_Sluiten_Exit() {
  // <nothing>
}
//Functions
//Functie die aangeeft of de poort gesloten is.
boolean poortGesloten() {
  return (poort_State == POORT_GESLOTEN);
}

//Functie die de servo in de meegegeven stand zet.
void zetServoRichtingStand(unsigned char hoek) {
  unsigned char huidigeHoek = poort.read();
  if (isTimeElapsed(BEWEEGTIJD, poortBeweegTimer)) {
    poortBeweegTimer = millis();
    if (hoek > huidigeHoek) {
      poort.write(huidigeHoek + 1);
    }
    else {
      poort.write(huidigeHoek - 1);
    }
  }
}

void openPoort() {
  while (poort.read() < GEOPEND) {
    zetServoRichtingStand(GEOPEND);
  }
}

void sluitPoort() {
  while (poort.read() > GESLOTEN) {
    zetServoRichtingStand(GESLOTEN);
  }
}

boolean poortGeopend(){
  return poort_State == POORT_OPEN;
}

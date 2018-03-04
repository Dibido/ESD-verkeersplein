// Module Button

//Number of buttons
const unsigned char NUMBEROFBUTTONS = 3;
//Button pins
const unsigned char BUTTON_PINS[NUMBEROFBUTTONS] = {A2, A0, A1};
// Button states
unsigned char button_States[NUMBEROFBUTTONS];
//Button switch states
boolean button_switch_States[NUMBEROFBUTTONS];
// Timer variables
// Time button needs to be pressed to record a buttonpress
const int BUTTON_INTERVAL = 10;
unsigned long button_Previous[NUMBEROFBUTTONS];

//To check whether a button is pressed
boolean buttonPressed(unsigned char pin) {
  return button_switch_States[pin];
}

//to check if the hardware button is down
boolean buttonHardware_Down(unsigned char pin) {
  return (digitalRead(BUTTON_PINS[pin]) == LOW);
}

//to check if the hardware button is up
boolean buttonHardware_Up(unsigned char pin) {
  return !buttonHardware_Down(pin);
}

// --- States -----------
const unsigned char BUTTON_STATE_RELEASED = 1;
const unsigned char BUTTON_STATE_CHECK_PRESSED = 2;
const unsigned char BUTTON_STATE_PRESSED = 3;
const unsigned char BUTTON_STATE_CHECK_RELEASED = 4;


// --- Setup -------------------
void button_Setup() {
  //Set the buttons to input
  for (int i = 0; i < NUMBEROFBUTTONS; i++) {
    pinMode(BUTTON_PINS[i], INPUT);
    button_States[i] = BUTTON_STATE_RELEASED;
    button_switch_States[i] = false;
  }
  // Start state
  button_Released_Entry();
}
// --- Loop --------------------
void button_Loop() {
  for (unsigned char button = 0; button < NUMBEROFBUTTONS; button++) {
    switch (button_States[button]) {
      case BUTTON_STATE_RELEASED:
        button_Released_Do();
        if (buttonHardware_Down(button) == true) {
          button_Released_Exit(button);
          button_States[button] = BUTTON_STATE_CHECK_PRESSED;
          button_Check_Pressed_Entry(button);
        }
        break;
      case BUTTON_STATE_CHECK_PRESSED:
        button_Check_Pressed_Do();
        if (buttonHardware_Up(button) == true) {
          button_Check_Pressed_Exit();
          button_States[button] = BUTTON_STATE_RELEASED;
          button_Released_Entry();
        }
        else if ((buttonHardware_Down(button) == true)
                 && (millis() - BUTTON_INTERVAL >= button_Previous[button])) {
          button_Check_Pressed_Exit();
          button_States[button] = BUTTON_STATE_PRESSED;
          button_Pressed_Entry();
        }
        break;
      case BUTTON_STATE_PRESSED:
        button_Pressed_Do();
        if (buttonHardware_Up(button) == true) {
          button_Pressed_Exit();
          button_States[button] = BUTTON_STATE_CHECK_RELEASED;
          button_Check_Released_Entry(button);
        }
        break;
      case BUTTON_STATE_CHECK_RELEASED:
        button_Check_Released_Do();
        if (buttonHardware_Down(button) == true) {
          button_Check_Released_Exit();
          button_States[button] = BUTTON_STATE_PRESSED;
          button_Pressed_Entry();
        }
        else if ((buttonHardware_Up(button) == true)
                 && (millis() - BUTTON_INTERVAL >= button_Previous[button])) {
          button_Check_Released_Exit();
          button_States[button] = BUTTON_STATE_RELEASED;
          button_Released_Entry();
        }
        break;
    }
  }
}
// --- BUTTON_STATE_RELEASED -----------
void button_Released_Entry() {
  // <nothing>
}
void button_Released_Do() {
  // <nothing>
}
void button_Released_Exit(unsigned char button) {
  button_switch_States[button] = !button_switch_States[button];
}
// --- BUTTON_STATE_CHECK_PRESSED -----------
void button_Check_Pressed_Entry(unsigned char button) {
  button_Previous[button] = millis();
}
void button_Check_Pressed_Do() {
  // <nothing>
}
void button_Check_Pressed_Exit() {
  // <nothing>
}
// --- BUTTON_STATE_PRESSED -----------
void button_Pressed_Entry() {
  // <nothing>
}
void button_Pressed_Do() {
  // <nothing>
}
void button_Pressed_Exit() {
  // <nothing>
}
// --- BUTTON_STATE_CHECK_RELEASED -----------
void button_Check_Released_Entry(unsigned char button) {
  button_Previous[button] = millis();
}
void button_Check_Released_Do() {
  // <nothing>
}
void button_Check_Released_Exit() {
  // <nothing>
}

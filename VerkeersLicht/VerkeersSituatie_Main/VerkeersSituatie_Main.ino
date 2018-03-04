/*
 * Title : VerkeersSituatie
 * Author : Dibran Dokter 587252
 * Klas : I1DD
 * Date : 4-04-2017
 * Decription : Statemachine voor een verkeerssituatie.
 */

//Setup all hardware and statemachines
void setup(void) {
  Serial.begin(9600);
  led_Setup();
  verkeersLicht_Setup();
  button_Setup();
  servo_Setup();
  poort_Setup();
  display_Setup();
  beeper_Setup();
  oversteken_Setup();
  ldr_Setup();
  nachtstand_Setup();
}

//Call all the loop functions of the statemachines
void loop(void) {
  verkeersLicht_Loop();
  button_Loop();
  poort_Loop();
  oversteken_Loop();
  nachtstand_Loop();
}

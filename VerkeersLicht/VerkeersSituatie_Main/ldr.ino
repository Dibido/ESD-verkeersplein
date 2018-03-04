//Set LDR pin.
const unsigned char LDRPIN = A3;

void ldr_Setup(){
  //Set LDR to input.
  pinMode(LDRPIN, INPUT);
}

//Function to read the LDR value.
int readLDR(){
 return analogRead(LDRPIN); 
}

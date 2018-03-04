//Timer function to check whether a certain amount of time has elapsed.
boolean isTimeElapsed(unsigned long delayTime, unsigned long previousMillis) {
  unsigned long currentTime = millis();
  if ((currentTime - previousMillis) > delayTime) {
    return true;
  }
  return false;
}

bool statePower = false; // start off
bool lastSwitchState = false;
unsigned long lastPowerOffDelay = 0UL;


void setup() {
  pinMode(2,INPUT_PULLUP); // power down switch
  pinMode(3,INPUT_PULLUP); // safe shutdown from Rpi
  pinMode(4,OUTPUT); // start software shutdown
  digitalWrite(4,LOW);
  pinMode(5,OUTPUT); // kill power
  digitalWrite(5,LOW);
}

void loop() {
  if (digitalRead(2) == LOW && lastSwitchState == false;) lastSwitchState = true;
  else if (digitalRead(2) == HIGH && lastSwitchState == true) {
    if (statePower == false) {
      statePower = true;
      digitalWrite(5,HIGH);
    }
  }
}

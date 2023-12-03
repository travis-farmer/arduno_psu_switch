/*
// on Rpi: /boot/config.txt
// dtoverlay=gpio-shutdown,gpio_pin=22,active_low=0,gpio_pull=off
// dtoverlay=gpio-poweroff,gpiopin=17,active_high
//
// gpio22 connected <-- to D4 via a NPN transistor, 3.3v pull-up resistor.
// gpio17 connected --> to NPN transistor to D3, 5v pull-up internal to Arduino.
// both NPNs have a 1k base resistor.
*/

bool statePower = false; // start off
bool lastSwitchState = false;
bool stateSafeShutdown = false;
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
  if (digitalRead(2) == LOW && lastSwitchState == false) lastSwitchState = true;
  else if (digitalRead(2) == HIGH && lastSwitchState == true) {
    if (statePower == false) {
      statePower = true;
      digitalWrite(5,HIGH);
    } else {
      digitalWrite(4,HIGH);
      lastPowerOffDelay = millis();
      while (stateSafeShutdown == false && millis() - lastPowerOffDelay < 60000) {
        if (digitalRead(3) == LOW) stateSafeShutdown = true;
      }
      delay(5000);
      digitalWrite(5,LOW);
      statePower = false;
    }
  }
}

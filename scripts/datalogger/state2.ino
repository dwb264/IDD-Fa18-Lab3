bool setUp2 = false;

void state2Setup() {
  lcd.clear();
  lcd.setCursor(0,0);
  if (eeAddress == EEPROMSIZE) {
    lcd.print("Memory full");
  } else {
    lcd.print("Logging stopped");
  }
  
  lcd.setCursor(0,1);
  lcd.print("Printing data...");

  readData();

  lcd.clear();
  lcd.print("Data printed");
  lcd.setCursor(0,1);
  lcd.print("Push to restart>");
  setUp2 = true;
}

void state2Loop() {
  // Reset and go to state 0 if button has been pressed
  buttonState = digitalRead(buttonPin);

  if (buttonState != lastButtonState) {
    
    if (buttonState == LOW) {
      lcd.clear();
      lcd.print("Resetting...");

      // Reset
      setUp0 = false, setUp1 = false, setUp2 = false;
      clearEEPROM();
      eeAddress = 0;
      
      state = 0;
    }

   lastButtonState = buttonState;
   
  }
}

void doState2() {
  if (!setUp2) { state2Setup(); }
  state2Loop();
}

// Read data stored in EEPROM, format and print to serial monitor
void readData() {
  Serial.println("Reading from EEPROM");
  int scaledLightThreshold = map(lightThreshold, 0, 1023, 0, 255);

  // Stats
  int onCount = 0;
  int offCount = 0;
  int changes = 0;

  int numRecords = min(eeAddress, EEPROMSIZE);

  Serial.print("time\tvalue\tstatus\n");
  Serial.print("------------------------\n");
  for (int i = 0; i < numRecords; i++) {
    value = EEPROM.read(i);
    Serial.print(formatTime(i) + "\t" + String(value) + "\t");
    if (value >= scaledLightThreshold) {
      Serial.print("ON\n");
      onCount++;
    } else {
      Serial.print("OFF\n");
      offCount++;
    }

    if (i > 0 && (
      (EEPROM.read(i) >= scaledLightThreshold && EEPROM.read(i-1) < scaledLightThreshold) || 
      (EEPROM.read(i) < scaledLightThreshold && EEPROM.read(i-1) >= scaledLightThreshold))
      ) {
      changes++;
    }
  }
  
  Serial.print("------------------------\n\n");
  
  Serial.print("SUMMARY\n");
  Serial.print("------------------------\n"); 
  Serial.print("ON:\t"    + String(onCount / 60.)  + "min (" + String(float(onCount)  * 100 / numRecords) + "%)\n");
  Serial.print("OFF:\t"   + String(offCount / 60.) + "min (" + String(float(offCount) * 100 / numRecords) + "%)\n");
  Serial.print("FLIPS:\t" + String(changes) + "\n\n");

  Serial.println("Done reading from EEPROM");
}

// Convert seconds to MM:SS
String formatTime(int seconds) {
  int intMin = seconds / 60;
  String minutes = String(intMin);
  String sec = String(seconds - (intMin * 60));
  if (minutes.length() == 1) {
    minutes = "0" + minutes;
  }
  if (sec.length() == 1) {
    sec = "0" + sec;
  }
  return minutes + ":" + sec;
   
}

void clearEEPROM() {
  // Clear data
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}

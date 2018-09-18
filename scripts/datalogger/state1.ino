bool setUp1 = false;

void state1Setup() {
  lcd.clear();
  setUp1 = true;
}

void state1Loop() {
  
  if (eeAddress < EEPROMSIZE && state == 1) {

    // Record photocell reading
    photocellReading = analogRead(photocellPin);  
  
    lcd.setCursor(0,0);
    lcd.print("Logging");
    
    lcd.setCursor(0,1);
    if (photocellReading >= lightThreshold) {
      lcd.print("Light is ON ");
    } else {
      lcd.print("Light is OFF");
    }
  
    logData();
    delay(10); // Change to 1000 for 1s, or 60000 for 1m
    
  } else {
    state = 2;
  }
  
}

void doState1() {
  if (!setUp1) { state1Setup(); }
  state1Loop();
}

void logData() {
  
  byte val = map(photocellReading, 0, 1023, 0, 255);

  // Write data
  EEPROM.write(eeAddress, val);

  // Move eeAddress to next available byte
  eeAddress += 1;
  
}

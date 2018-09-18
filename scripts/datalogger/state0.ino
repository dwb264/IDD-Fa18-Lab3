bool setUp0 = false;

void state0Setup() {
  
  lcd.clear();
  lcd.print("Turn light on");
  lcd.setCursor(0,1);
  lcd.print("Push to continue>");
  
  setUp0 = true;
  
}

void state0Loop() {

  // read the pushbutton input pin:
  buttonState = digitalRead(buttonPin);

  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    if (buttonState == LOW) {
      int reading = analogRead(photocellPin);
      lightThreshold = reading * 0.75; // Give room for error
      state = 1;
    }
    
    lastButtonState = buttonState;
    
  }

  delay(10);
  
}

void doState0() {
  if (!setUp0) { state0Setup(); }
  state0Loop();
}

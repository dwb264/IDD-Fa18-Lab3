/* Light Data Logger
 *  
 * Records data about whether a light is on or off using photocell sensor
 *
*/

#include <EEPROM.h>
#include <LiquidCrystal.h>
 
int photocellPin = 1;     // the cell and 10K pulldown are connected to a0
int photocellReading;     // the analog reading from the sensor divider
int buttonPin = 7;
int buttonState = 0;
int lastButtonState;

int eeAddress = 0;
byte value;
const int EEPROMSIZE=1024;

int lightThreshold = 40; // min digital sensor value where the light is ON

int state, lastState = -1;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup(void) {
  // We'll send debugging information via the Serial monitor
  Serial.begin(9600);   
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  lcd.begin(16, 2);
  state = 0;
}

void loop(void) {

  switch (state) {
  case 0:    
    doState0();
    break;
  case 1:    
    doState1();
    break;
  case 2:    
    doState2();
    break;
  }
  lastState = state;

}

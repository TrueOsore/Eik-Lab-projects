// ------------------
// Libraries
// ------------------
#include <LiquidCrystal_I2C.h>
#include <CodeCell.h>


// ------------------
// Variable declaration
// ------------------
CodeCell myCodeCell;
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define heartratePin 1 // GPIO1


// ------------------
// Setup & Loop
// ------------------
int beats = 0; // Amount of beats
int prev_beat = 0;
int lastTime = 0;

void setup() {
  Serial.begin(115200); // To pr
  myCodeCell.Init(LIGHT + MOTION_STATE + MOTION_STEP_COUNTER);   // CodeCell automatically initializes GPIO8  and GPIO9 as I2C pins

  // LCD configuration
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop() {
  if (myCodeCell.Run(10)) {
    // Collect sensor data
    uint16_t proximity = myCodeCell.Light_ProximityRead();
    uint16_t motion_state = myCodeCell.Motion_StateRead();
    uint16_t steps = myCodeCell.Motion_StepCounterRead();

    // Calculate heart beart
    uint8_t beat = myCodeCell.pinADC(heartratePin); // Read heartbeat data from pin (0, 255)

    if ((beat - prev_beat) > 200) { // Detect a beat when signal goes from high/low
      beats++;
    }

    prev_beat = beat;

    if ((millis() - lastTime) >= 5000) { // Run once every 5 seconds
      lcd.clear();

      lastTime = millis();
      int BPM = beats * (60.0 / 5.0);

      lcd.setCursor(0, 1);
      lcd.print("BPM: " + String(BPM));

      Serial.println("BPM: " + String(BPM));

      beats = 0;
    }

    // Screen


    lcd.setCursor(0, 0);
    lcd.print("Steps: " + String(steps));
  }
}

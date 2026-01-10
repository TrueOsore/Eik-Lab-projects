#include <CodeCell.h>
#include "MicroLink.h"

#define heartratePin 1

CodeCell myCodeCell;
MicroLink myMicroLink;

void setup() {
  Serial.begin(115200);  // Start USB serial at 115200 baud (enable USB_CDC_On_Boot for Serial)

  // Initialize CodeCell sensors
  myCodeCell.Init(MOTION_STEP_COUNTER + MOTION_STATE);  // Enable sensors

  // Initialize Microlink Bluetooth
  myMicroLink.Init();
}

int beats = 0; // Amount of beats
int prev_beat = 0;
int lastTime = 0;

void loop() {
  if (myCodeCell.Run(10)) { // Runs at 10 Hz (10 times per second)
    uint8_t beat = myCodeCell.pinADC(heartratePin); // Read heartbeat data from pin (0, 255)

    if ((beat - prev_beat) > 200) { // Detect a beat when signal goes from high/low
      beats++;
    }
    prev_beat = beat;

    // Create variables for sensors
    uint16_t steps = myCodeCell.Motion_StepCounterRead();
    uint16_t state = myCodeCell.Motion_ActivityRead();

    myMicroLink.ShowSensors(myCodeCell.BatteryLevelRead(), steps, 0);

    // Convert current beat value into a percentage
    uint8_t beat_percent = (beat * 100) / 255;

    myCodeCell.pinPWM(2, 1000, beat_percent);
  }

  if ((millis() - lastTime) >= 5000) { // Run once every 5 seconds
    lastTime = millis();
    int BPM = beats * (60.0 / 5.0);

    char bpm_text[21];
    sprintf(bpm_text, "BPM %u", BPM); // This string is compatible for myMicroLink.Print()

    myMicroLink.Print(bpm_text);

    beats = 0;
  }
}


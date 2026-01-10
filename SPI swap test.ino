// ------------------
// Libraries
// ------------------
#include <CodeCell.h>
#include <Adafruit_GFX.h>
#include <Adafruit_GC9A01A.h>

// ------------------
// Defined pins
// ------------------
#define TFT_MOSI 8    // SDA / DIN on display
#define TFT_SCLK 9    // SCL / CLK on display
#define TFT_CS   6
#define TFT_DC   5
#define TFT_RST  7

#define heartratePin 1

// ------------------
// Variable declaration
// ------------------
CodeCell myCodeCell;
Adafruit_GC9A01A tft(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

// ------------------
// Function definitions
// ------------------
void pain(int steps, int beats) {
  // Adafruit

  tft.begin();
  tft.fillScreen(GC9A01A_BLACK);
  tft.setTextColor(GC9A01A_WHITE);
  
  tft.setTextSize(2);
  tft.setCursor(100, 110);
  tft.println("Steps: " + String(steps));
  
  tft.setCursor(100, 140); 
  tft.println("BPM: " + String(beats));
  myCodeCell.Init(MOTION_MAGNETOMETER);
}

// ------------------
// Loop
// ------------------
void setup() {
  Serial.begin(115200);
  myCodeCell.Init(MOTION_MAGNETOMETER);
}

int beats = 0; // Amount of beats
int prev_beat = 0;
int lastTime = 0;


float x = 0.0;  // X-axis acceleration
float y = 0.0;  // Y-axis acceleration
float z = 0.0;  // Z-axis acceleration

void loop() {

  //   if (myCodeCell.Run(10)) { // Runs at 10 Hz (10 times per second)
  //     uint8_t beat = myCodeCell.pinADC(heartratePin); // Read heartbeat data from pin (0, 255)

  //   if ((beat - prev_beat) > 200) { // Detect a beat when signal goes from high/low
  //     beats++;
  //   }
  //   prev_beat = beat;
  // }

  // if ((millis() - lastTime) >= 5000) { // Run once every 5 seconds
  //   lastTime = millis();
  //   int BPM = beats * (60.0 / 5.0);
  //   beats = 0;
  // }



  myCodeCell.Motion_MagnetometerRead(x, y, z);
  uint8_t beat = myCodeCell.pinADC(heartratePin);
  Serial.println(x + y + z);

  uint16_t steps = 0;

  pain(steps, beat);
}




  // // Basic visual proof
  // tft.fillScreen(GC9A01A_BLACK);
  // delay(200);
  // tft.fillScreen(GC9A01A_RED);
  // delay(200);
  // tft.fillScreen(GC9A01A_GREEN);
  // delay(200);
  // tft.fillScreen(GC9A01A_BLUE);
  // delay(200);

  // // Text test
  // tft.fillScreen(GC9A01A_BLACK);
  // tft.setTextColor(GC9A01A_WHITE);
  // tft.setTextSize(2);
  // tft.setCursor(30, 110);
  // tft.println("GC9A01A OK");
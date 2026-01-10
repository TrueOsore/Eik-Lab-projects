## What I Did

I tried using the **GC9A01A** screen with an **ESP32**. Initially, I tried the **TFT_eSPI** library, but discovered that it is only compatible with version **2.x** of the ESP32 core. The **CodeCell** library, which is required to use the built-in sensors, requires version **3.x** of the ESP32 core.

I then decided to use the **Adafruit** library, as it is compatible with ESP32 core version **3.x**. This worked; however, these libraries use a single SPI lane. The **CodeCell C3** only has one SPI lane available. One solution I considered was constantly switching between the libraries. While this would work in theory, the frequent switching caused significant slowdowns. Another issue is that the CodeCell library expects the sensors to be active at all times, so enabling and disabling the library caused failures.

## I2C as a Possible Solution

A theory I came up with was that using an **I2C display** would solve these issues, as it would not occupy the SPI lane. This would allow the CodeCell library to use SPI without interference.

## Conclusion

In conclusion, the **GC9A01A** display will not work in this setup due to it being an SPI-based module. The next step was therefore to try an **I2C display**. The **CodeCell C3** automatically initializes the I2C pins on **GPIO8** and **GPIO9**. With the help of the **LiquidCrystal_I2C** library, I was able to connect the display to the CodeCell without any issues.

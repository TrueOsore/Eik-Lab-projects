Project time: 2 weeks

This project was about making a "health monitor" with the CodeCell C3 and the DFRobot SKU SEN0203 (heart rate sensor).

I started this project by first learning how to use the CodeCell C3 from the provided documents. Then I connected the heartrate sensor to the CodeCell using wires, one to ground, one to the 3.3v header and one to GPIO 101. I initially encountered some issues, as the DFRobot documentation mentioned the sensor wanted a 5v pin. This issue was fixed when I switched to the 3.3v one.

One of the problems I encountered when doing this project was being able to use the libraries for the DFRobot heart rate sensor. The problem was that when the sensor was connected through the CodeCell, the CodeCell's ADC pins would read the input values as a number that the DFRobot-library did not accept. I then had to create my own algorithm to check the heartrate. The solution was not perfect, but it could give a rough estimate of the current heartrate. After reading some more, I discovered that the DFRobot-library was coded for the Arduino Uno which I believe have different pin logic. I also found that the sketching and uploading of code to the CodeCell took an unreasonable amount of time, almost 2-3 minutes each time. The amount of code changed didn't matter either.

Then I managed to connect the CodeCell C3 to the MicroLink app. This was done with the CodeCell's Bluetooth functionality. I also added the ability to track the amount of steps. My last step was to connect the CodeCell to a breadboard with an led that would pulsate together with your heartrate. I was able to do that with CodeCell's PWN function, as the GPIO pin would only give on/off signals while in digital mode (binary signals).

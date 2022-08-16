// Example usage for MMA7660-Accelerometer library by Julian Adenauer <julian@retune.de>.

#include <MMA7660-Accelerometer.h>

MMA7660 accelerometer;

void setup() {
    accelerometer.init();
    Serial.begin(115200);
}

void loop() {
    float x, y, z;
    accelerometer.getAcceleration(&x, &y, &z);

    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.println(z);

    delay(100);
}

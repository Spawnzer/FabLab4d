/*
 * Project Display
 * Description: display a counter on a 4digits 7segment display 
 * Author: Philippe Libioulle
 * Date:
 */

#include <TM1637Display.h>
#include <MMA7660-Accelerometer.h>
#include <Grove_ChainableLED.h>
#define NUM_LEDS  1
#define CLK D4
#define DIO D5
TM1637Display display(CLK,DIO);
ChainableLED leds(D2, D3, NUM_LEDS);
SerialLogHandler logHandler;
MMA7660 accelerometer;

bool isAlertOn = false;
int cnt;
system_tick_t alertTime;
system_tick_t validityPeriod = 2000;   // in ms

void myHandler(const char *event, const char *data)
{  
  Log.info("event=%s data=%s", event, (data ? data : "NULL"));
  isAlertOn = true;
  alertTime = millis();
}

void setup() {
  isAlertOn = false;  
   accelerometer.init();
  display.setBrightness(0xff);                   //set the diplay to maximum brightness  
  display.showNumberDec(1234, true, 4, 0);       // just a display test
  delay(1000); 
  Particle.subscribe("Alert", myHandler);        //subscribe to the Alert event
  Log.info("Started");
  leds.init();
}

void loop() {
  
  
      /*if (cnt == 9999) {cnt = 0;}
      cnt++;*/
        
  int8_t x = 0;
  int8_t y = 0;
  int8_t z = 0;
  //int i = 0;
  int a = 0;
  int c = 0;
  int lc = 0; 
  accelerometer.getXYZ(&x, &y, &z);
  int8_t baseX = x;
  int8_t baseY = y;
  int8_t baseZ = z;
  int8_t deltaX = 0;
  int8_t deltaY = 0;
  int8_t deltaZ = 0;
  //float ax, ay, az;
  
  //cnt = ((x%10) * 100) + ((y%10) * 10) + (z%10);
  while(1)
  {
    accelerometer.getXYZ(&x, &y, &z);
    delay(1000);
    Log.info("X: %d", x);
    Log.info("Y: %d", y); 
    Log.info("Z: %d", z);
    x > baseX ? deltaX = x - baseX : deltaX = baseX - x;
    y > baseY ? deltaY = y - baseY : deltaY = baseY - y;
    z > baseZ ? deltaZ = z - baseZ : deltaZ = baseZ - z;
    deltaX > deltaY ? (deltaX > deltaZ ? a = deltaX : a = deltaZ) : (deltaY > deltaZ ? a = deltaY : a = deltaZ);
    a <= 10 ? leds.setColorRGB(0, 0, 255, 0): (a <= 20 ? leds.setColorRGB(0, 255, 140, 0): leds.setColorRGB(0, 255, 0, 0));  
    a <= 10 ? c = 0: (a <= 20 ? c = 1 : c = 2); 
    c == lc ? cnt++ : cnt = 0;
    lc = c;
    display.showNumberDec(cnt, true, 4, 0);
    /*i++;
    if (i > 10)
    {
      accelerometer.getXYZ(&x, &y, &z);
      baseX = x;
      baseY = y;
      baseZ = z;
      i = 0;
    }*/
  }
  
  
  
  /*accelerometer.getAcceleration(&ax, &ay, &az);
  Log.info("AX: %f", ax);
  Log.info("AY: %f", ay);
  Log.info("AZ: %f", az);*/


}

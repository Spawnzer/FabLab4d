/* MMA7660-Accelerometer library by seeed technology inc. / Frankie Chu
 */

#include "MMA7660-Accelerometer.h"

/*Function: Write a byte to the register of the MMA7660*/
void MMA7660::write(uint8_t _register, uint8_t _data)
{
    Wire.begin();
    Wire.beginTransmission(MMA7660_ADDR);
    Wire.write(_register);
    Wire.write(_data);
    Wire.endTransmission();
}
/*Function: Read a byte from the regitster of the MMA7660*/
uint8_t MMA7660::read(uint8_t _register)
{
    uint8_t data_read = 0;
    Wire.begin();
    Wire.beginTransmission(MMA7660_ADDR);
    Wire.write(_register);
    Wire.endTransmission();
    Wire.beginTransmission(MMA7660_ADDR);
    Wire.requestFrom(MMA7660_ADDR,1);
    while(Wire.available())
    {
        data_read = Wire.read();
    }
    Wire.endTransmission();
    return data_read;
}

void MMA7660::init()
{
    setMode(MMA7660_STAND_BY);
    setSampleRate(AUTO_SLEEP_32);
    setMode(MMA7660_ACTIVE);
}
void MMA7660::setMode(uint8_t mode)
{
    write(MMA7660_MODE,mode);
}
void MMA7660::setSampleRate(uint8_t rate)
{
    write(MMA7660_SR,rate);
}
/*Function: Get the contents of the registers in the MMA7660*/
/*          so as to calculate the acceleration.            */
void MMA7660::getXYZ(int8_t *x,int8_t *y,int8_t *z)
{
    unsigned char val[3];
    int count = 0;
    int timeout = 0;

    val[0] = val[1] = val[2] = 64;
    while(Wire.available() > 0)
    {
        Wire.read();
        delay(1);
        if(timeout++ > 100) break;
    }

    Wire.requestFrom(MMA7660_ADDR,3);
    while(Wire.available())
    {
        if(count < 3)
        {
            while ( val[count] > 63 )  // reload the damn thing it is bad
            {
              val[count] = Wire.read();
            }
        }
        count++;
    }
    *x = ((char)(val[0]<<2))/4;
    *y = ((char)(val[1]<<2))/4;
    *z = ((char)(val[2]<<2))/4;
}

void MMA7660::getAcceleration(float *ax,float *ay,float *az)
{
    int8_t x,y,z;
    getXYZ(&x,&y,&z);
    *ax = x/21.00;
    *ay = y/21.00;
    *az = z/21.00;
}

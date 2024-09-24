
//#include <HardwareSerial.h>
#include<BluetoothSerial.h>
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to enable it
#endif

//HardwareSerial SerialUart(2); // RX, TX
BluetoothSerial SerialBT;

unsigned char data[4]={};
float distance;

void setup()
{
 Serial.begin(115200);
 Serial2.begin(9600,SERIAL_8N1, 16, 17); 
 SerialBT.begin("ESP32");
 Serial.print("Bluethoot device is ready to pair");
}

void loop()
{
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=Serial2.read();
     }
  }while(Serial2.read()==0xff);//reading the data untill 4 bytes is full(1020)

  Serial2.flush();//it will wait until previous data read successfully


  if(data[0]==0xff)//if data on 0 position is 255; 
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;//that is syntax
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
        if(distance>30)
          {
           Serial.print("distance=");
           Serial.print(distance/10);
           Serial.println("cm");
           SerialBT.print("ultraSonic value:");
           SerialBT.println(distance/10);
          }else 
             {
               Serial.println("Below the lower limit");
             }
      }else Serial.println("ERROR");
     }

     delay(100);
}

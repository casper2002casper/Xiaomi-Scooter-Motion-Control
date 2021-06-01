#include <Arduino.h>
#include "XiaomiScooterPro.h"

#define SIZE_VALID_MSG 10
#define BUFF_SIZE 256
uint8_t buff[BUFF_SIZE];

XiaomiScooterPro scooter = XiaomiScooterPro();

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available() > 0) {//Receive msg from scooter motor controller
    int msgLen = Serial.readBytes(buff, BUFF_SIZE);
    if(msgLen > SIZE_VALID_MSG){
      scooter.update(buff);
    }
  }
  scooter.control();
}

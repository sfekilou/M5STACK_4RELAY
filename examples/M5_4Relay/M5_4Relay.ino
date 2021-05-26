/* Exemple with M5StickC module */
#include <Arduino.h>
#include <M5StickC.h> //For M5StickC module
#include <Wire.h>
#include "M5_4Relay.h"

M5_4Relay Relay4;

void setup()
{
 uint16_t state;
 
 //this line for M5StickC: 
 M5.Axp.begin(true,true,false,false,true); //DCDC1 & RTCvoltage are ON (false) - DCDC1 must be ON for M5SticK
 
 Serial.begin(115200);
 delay(1500);
 Relay4.begin(Wire1,32,33); //initiate I2C on Wire1, SDA=32, SCL=33
 Relay4.SyncMode(true); //light the LEDs where relays is ON state
 Relay4.AllOff(); //All relays to OFF
 state=Relay4.ReadState(); //read 0x10 & 0x11 registers
 Serial.printf("State1= %x\n",state);
 delay(5000);
 Relay4.Write4Relay(0,true); //Relay 0 ON
 Relay4.Write4Relay(1,true); //Relay 1 ON
 Relay4.Write4Relay(2,false); //Relay 2 OFF
 Relay4.Write4Relay(3,true); //Relay 3 ON
 state=Relay4.ReadState();
 Serial.printf("State2= %x\n",state);
 delay(5000);
 Relay4.SyncMode(false);
 Relay4.AllOff();
 delay(5000);
 Relay4.Write4Relay(0,true);
 Relay4.Write4Relay(1,true);
 Relay4.Write4Relay(2,false);
 Relay4.Write4Relay(3,true);
 state=Relay4.ReadState();
 Serial.printf("State3= %x\n",state);
 delay(5000);
 Relay4.SyncMode(true); //light the LEDs where relays is ON state
}

void loop()
{
 delay(500);
 Relay4.SyncMode(false); //light off the LEDs
 delay(500);
 Relay4.SyncMode(true); //light the LEDs where relays are ON state
}

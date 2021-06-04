/*
    M5_4Relay example sketch
    This sketch shows how to use the 4-Relay Unit of M5Stack.
    V1.1.0
*/

#include <Arduino.h>
#include <M5StickC.h> //For M5StickC module
#include <Wire.h>
#include <M5_4Relay.h>

M5_4Relay Relay4;

void setup()
{
 uint16_t state;
 
 M5.Axp.begin(true,true,false,false,true); //This line for M5StickC - DCDC1 & RTCvoltage are ON (false) - DCDC1 must be ON for M5StikC
 
 Serial.begin(115200);
 delay(1500);
 Relay4.begin(Wire1,32,33); //initiate I2C on Wire1, SDA=32, SCL=33
 Relay4.SyncMode(true); //light the LEDs where relays is ON state
 Relay4.AllOff(); //All relays will be OFF
 state=Relay4.ReadState(); //read 0x10 & 0x11 registers, state will contains registers 0x10 (high byte) and 0x11 (low byte)
 delay(5000);
 Relay4.Write4Relay(0,true); //Relay 0 ON
 Relay4.Write4Relay(1,true); //Relay 1 ON
 Relay4.Write4Relay(2,false); //Relay 2 OFF
 Relay4.Write4Relay(3,true); //Relay 3 ON
 state=Relay4.ReadState();
 delay(5000);
 Relay4.SyncMode(false);
 Relay4.AllOff();
 delay(5000);
 Relay4.Write4Relay(0,true);  //set relay 0 ON
 Relay4.Write4Relay(1,true);  //set relay 1 ON 
 Relay4.Write4Relay(2,false); //set relay 2 OFF
 Relay4.Write4Relay(3,true);  //set relay 3 ON
 state=Relay4.ReadState();
 delay(5000);
 Relay4.SyncMode(true); //light the LEDs where relays is ON state
 Serial.println(Relay4.GetStateRelayNb(0)); //get & print state of relay 0
 Serial.println(Relay4.GetStateRelayNb(1)); //get & print state of relay 1
 Serial.println(Relay4.GetStateRelayNb(2)); //get & print state of relay 2
 Serial.println(Relay4.GetStateRelayNb(3)); //get & print state of relay 3
 delay(5000);
 Relay4.Write4Relay(0,false); //set relay 0 OFF
 Relay4.Write4Relay(1,false); //set relay 1 OFF
 Relay4.Write4Relay(2,true);  //set relay 2 ON
 Relay4.Write4Relay(3,false); //set relay 3 OFF
 Serial.println(Relay4.GetStateRelayNb(0)); //get & print state of relay 0
 Serial.println(Relay4.GetStateRelayNb(1)); //get & print state of relay 1
 Serial.println(Relay4.GetStateRelayNb(2)); //get & print state of relay 2
 Serial.println(Relay4.GetStateRelayNb(3)); //get & print state of relay 3
}

void loop()
{
 delay(500);
 Relay4.SyncMode(false); //light off the LEDs
 delay(500);
 Relay4.SyncMode(true); //light the LEDs where relays are ON state
}
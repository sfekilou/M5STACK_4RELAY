# M5STACK_4RELAY

Library for 4-RELAY unit from M5STACK

<a href="https://shop.m5stack.com/collections/m5-unit/products/4-relay-unit">
  <img src="https://shop.m5stack.com/cdn/shop/files/1_f75f486a-a5e5-4d05-a42f-c1559137bbac_1200x1200.jpg?v=1684305873" width="500px" />
</a>

Manufacturer's reference, description and documents: https://shop.m5stack.com/collections/m5-unit/products/4-relay-unit

Library functions
=================

void begin(TwoWire &wireport,int sdaPin, int sclPin,uint32_t frequency) //Initiate I2C

uint16_t ReadState() //read state of registers 0x10 & 0x11

bool GetStateRelayNb(int relayNB) //get state of relay number relayNB [0-3]

void SyncMode(bool Sync) //set LEDs sync or async whith their relays

void AllOff() //set all relays to OFF state

void Write4Relay(int number,bool state) //set state of relay number [0-3]

Short example:
```ino
#include <Arduino.h>
#include <M5StickC.h> //For M5StickC module
#include <Wire.h>
#include <M5_4Relay.h>

M5_4Relay Relay4;

void setup()
{
  M5.Axp.begin(true,true,false,false,true); //This line for M5StickC - DCDC1 & RTCvoltage are ON (false) - DCDC1 must be ON for M5StikC
 
  Serial.begin(115200);
  delay(1500);
  Relay4.begin(Wire1,32,33); //initiate I2C on Wire1, SDA=32, SCL=33
  Relay4.AllOff(); //All relays will be OFF
  Relay4.Write4Relay(0,true); //Relay 0 ON
  Relay4.Write4Relay(1,true); //Relay 1 ON
  Relay4.Write4Relay(2,false); //Relay 2 OFF
  Relay4.Write4Relay(3,true); //Relay 3 ON
  Serial.println(Relay4.GetStateRelayNb(0)); //get & print state of relay 0
  Serial.println(Relay4.GetStateRelayNb(1)); //get & print state of relay 1
  Serial.println(Relay4.GetStateRelayNb(2)); //get & print state of relay 2
  Serial.println(Relay4.GetStateRelayNb(3)); //get & print state of relay 3
}

void loop()
{
}
```


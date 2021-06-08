/*
  M5_4Relay.h
  4-Relay Unit of M5Stack library for Arduino
  by Louis Fesler
  Version 1.1.0
  My code uses the "MIT" license.
*/

#ifndef __M5_4Relay_H__
#define __M5_4Relay_H__

#define ADDR_I2C_4RELAY 0x26

class M5_4Relay {
public:
    M5_4Relay();
    void begin(TwoWire &wireport,int sda=-1,int scl=-1,uint32_t frequency=0);
    void Write4Relay(int number,bool state);
    bool GetStateRelayNb(int relayNB);
    uint16_t ReadState(void);
    void SyncMode(bool SyncMode);
    void AllOff();
private:
    TwoWire *i2cc;
    void write4R(int regAddr,int data);
    int read4R(int address);
}; 

#endif

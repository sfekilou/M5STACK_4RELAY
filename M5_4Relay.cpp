/*----------------------------------------------------------------------------
|RELAY control reg           | 0x10-0x11
|-----------------------------------------------------------------------------
|Relay_ctrl_mode_reg[0] 0x10 | R/W | System control
                             | 7 | 6 | 5 | 4 | 3 | 2 | 1 |     0     |
                             | R | R | R | R | R | R | R | Sync Mode |
                             | -Sync Mode:0 LED&Relay Async
                             | -Sync Mode:1 LED&Relay Sync
------------------------------------------------------------------------------
|Relay_ctrl_mode_reg[1] 0x11 | R/W | Relay & LED control
                             |  7  |  6  |  5  |  4  |  3  |  2  |  1  |  0  |
                             | LED1| LED2| LED3| LED4| RLY1| RLY2| RLY3| RLY4|
----------------------------------------------------------------------------*/

#include <Wire.h>
#include "M5_4Relay.h"

M5_4Relay::M5_4Relay()
{
}

/**
 * @brief Initialize I2C
 * @param wireport: Wire or Wire1, etc. On M5StickC, use Wire1
 * @param sda num GPIO
 * @param scl num GPIO
 * @param frequency: clock frequency
 */
void M5_4Relay::begin(TwoWire &wireport,int sdaPin, int sclPin,uint32_t frequency)
{  
 i2cc=&wireport;
 i2cc->begin(sdaPin,sclPin,frequency);
}

/**
 * @brief Read state of 2 registers (0x10 & 0x11)
 * 
 * @return uint16_t High byte: register 0x10, Low byte: register 0x11
 */
uint16_t M5_4Relay::ReadState()
{  
 uint16_t state;
 state=((uint16_t)read4R(0x10) & 0x00FF);
 state<<=8;
 state|=((uint16_t)read4R(0x11) & 0x00FF);
 return state;
}

/**
 * @brief Set relays and their LEDs sync or async.
 *  If new mode is true and before some relays are ON, the LED will set like relays corresponding.
 * @param SyncMode true: LEDs & relays Sync, false: LEDs & relays Async
 */
void M5_4Relay::SyncMode(bool Sync)
{
 if(Sync) write4R(0x10,1);
 else write4R(0x10,0);
}

/**
 * @brief Relays and LEDs will be set to OFF
 */
void M5_4Relay::AllOff()
{
 i2cc->beginTransmission(ADDR_I2C_4RELAY);
 i2cc->write(0x11);
 i2cc->write(0x00);
 i2cc->endTransmission();
}

/**
 * @brief Set relays ON or OFF
 * @param number relay number (0 or 1 or 2 or 3)
 * @param state true=ON, false=OFF
 */
void M5_4Relay::Write4Relay(int number,bool state)
{
 int StateRelayLED = read4R(0x11);
 if(state) StateRelayLED |= (0x01<<number);
 else StateRelayLED &= ~(0x01<<number);
 write4R(0x11,StateRelayLED);
}

void M5_4Relay::write4R(int regAddr,int data)
{
 i2cc->beginTransmission(ADDR_I2C_4RELAY);
 i2cc->write(regAddr);
 i2cc->write(data);
 i2cc->endTransmission();
}

int M5_4Relay::read4R(int regAddr)
{
 int state;
 i2cc->beginTransmission(ADDR_I2C_4RELAY);
 i2cc->write(regAddr);
 i2cc->endTransmission();
 i2cc->requestFrom(ADDR_I2C_4RELAY,1);
 state=i2cc->read() & 0x00ff;
 return state;	
}

#ifndef IRTRANSMITTER_HPP
#define IRTRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class IrTransmitter
{
    
private:
    hwlib::target::d2_36kHz & IrLED;
    uint16_t posLow;
    uint16_t posHigh;
    uint16_t negLow;
    uint16_t negHigh;
public:
    IrTransmitter(hwlib::target::d2_36kHz & IrLED, 
                  uint16_t low, 
                  uint16_t high):
    IrLED(IrLED), negHigh(low), negLow(high), posHigh(high), posLow(low){};
    
    IrTransmitter(hwlib::target::d2_36kHz & IrLED,
                  uint16_t negLow,
                  uint16_t negHigh,
                  uint16_t posLow, 
                  uint16_t posHigh):
    IrLED(IrLED), negHigh(negHigh), negLow(negLow), posHigh(posHigh), posLow(posLow){};
    void Send(bool b);
};

#endif // IRTRANSMITTER_HPP

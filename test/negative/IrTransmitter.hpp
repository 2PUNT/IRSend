#ifndef IRTRANSMITTER_HPP
#define IRTRANSMITTER_HPP

#include "hwlib.hpp"

class IrTransmitter 
{
    
private:
    hwlib::target::d2_36kHz & IrLED;
    
public:
    IrTransmitter(hwlib::target::d2_36kHz & IrLED): IrLED(IrLED){ };
    void Send(bool b);
};

#endif // IRTRANSMITTER_HPP


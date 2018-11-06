#ifndef IRTRANSMITTER_HPP
#define IRTRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class IrTransmitter
{

private:
    hwlib::target::d2_36kHz & IrLED;

public:
    IrTransmitter(hwlib::target::d2_36kHz & IrLED):IrLED(IrLED){};
    void Send(bool b){
          IrLED.set(b);
    };
};

#endif // IRTRANSMITTER_HPP

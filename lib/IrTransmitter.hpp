#ifndef IRTRANSMITTER_HPP
#define IRTRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class IrTransmitter
{

private:
    hwlib::target::d2_36kHz & IrLED;

public:

    //! Initialize a SendIrMessageControl object
    //! @param IrLED - 36khz IRLed needs to be used for PWM capbilities
    IrTransmitter(hwlib::target::d2_36kHz & IrLED):IrLED(IrLED){};


    //! @param b a boolean which is the new value of the IrLED until changed
    void Send(bool b){
          IrLED.set(b);
    };
};

#endif // IRTRANSMITTER_HPP

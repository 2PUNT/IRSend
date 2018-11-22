#ifndef IRTRANSMITTER_HPP
#define IRTRANSMITTER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

/// \brief An ir-transmitter
/// \details Uses the d2_36kHz pin to send ir-signals.
class IrTransmitter
{

private:
    hwlib::target::d2_36kHz & IrLED;

public:

    /// Construct a SendIrMessageControl object
    /// @param IrLED - 36khz IRLed needs to be used for PWM capbilities
    IrTransmitter(hwlib::target::d2_36kHz & IrLED):IrLED(IrLED){};


    /// @param b a boolean which is the new value of the IrLED until changed
    void Send(bool b){
          IrLED.set(b);
    };
};

#endif // IRTRANSMITTER_HPP

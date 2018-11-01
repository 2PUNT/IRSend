#include "IrTransmitter.hpp"

void IrTransmitter::Send(bool b)
{
    negHigh, negLow, posHigh, posLow
    auto buf = hwlib::buffering::unbuffered; // TODO: comment
    if(b){
        IrLED.set(true);
        hwlib::wait_us(posHigh);
        IrLED.set(false);
        hwlib::wait_us(posLow);
    }else{
        IrLED.set(true);
        hwlib::wait_us(negHigh);
        IrLED.set(false);
        hwlib::wait_us(negLow);
    }
}



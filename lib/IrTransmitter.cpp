#include "IrTransmitter.hpp"

void IrTransmitter::Send(bool b){ 
    if(b){
        uint16_t w1 = posHigh;
        uint16_t w2 = posLow;
    }else{
        uint16_t w1 = negHigh;
        uint16_t w2 = negLow;
    }
    IrLED.set(true);
    SendTimer.set( w1 );
    wait( SendTimer );
    IrLED.set(false);
    SendTimer.set( w2 );
    wait( SendTimer );
}




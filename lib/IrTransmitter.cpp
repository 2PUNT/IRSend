#include "IrTransmitter.hpp"

void IrTransmitter::Send(bool b){
    IrLED.set(b);
}

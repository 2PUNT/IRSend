#include "IrTransmitter.hpp"

void IrTransmitter::Send(bool b){ 
	auto buf = hwlib::buffering::unbuffered; // TODO: class dec
    IrLED.set(b, buf);
}




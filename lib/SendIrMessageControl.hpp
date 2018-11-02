#ifndef SENDIRMESSAGECONTROL_HPP
#define SENDIRMESSAGECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

class SendIrMessageControl :  public rtos::task<>
{

private:
    IrTransmitter & IrLED;
    uint16_t negHigh;
    uint16_t negLow;
    uint16_t posHigh;
    uint16_t posLow;
    rtos::timer SendTimer;
    rtos::channel< uint16_t, 16 > IRMessagesSendQueue;

public:
    SendIrMessageControl(IrTransmitter & IrLED,
                  uint16_t low,
                  uint16_t high,
                  int priority):
    task(priority, "SendIrMessageControl"), IrLED(IrLED), negHigh(low), negLow(high), posHigh(high), posLow(low), SendTimer( this, "SendTimer" ), IRMessagesSendQueue( this, "IRMessagesSendQueue" ){};

    SendIrMessageControl(IrTransmitter & IrLED,
                  uint16_t negLow,
                  uint16_t negHigh,
                  uint16_t posLow,
                  uint16_t posHigh,
                  int priority):
    task(priority, "SendIrMessageControl")IrLED(IrLED), negHigh(negHigh), negLow(negLow), posHigh(posHigh), posLow(posLow),SendTimer( this, "SendTimer" ), IRMessagesSendQueue( this, "IRMessagesSendQueue" ){};


    void sendMessage(uint16_t m);
    void main();
};

#endif // SENDIRMESSAGECONTROL_HPP

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
    rtos::channel< int, 16 > IRMessagesSendQueue;

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
    task(priority, "SendIrMessageControl"),IrLED(IrLED), negHigh(negHigh), negLow(negLow), posHigh(posHigh), posLow(posLow),SendTimer( this, "SendTimer" ), IRMessagesSendQueue( this, "IRMessagesSendQueue" ){};


    void sendMessage(uint16_t m){
        IRMessagesSendQueue.write(m);
    }
    void main(){
      enum class STATE {WAIT_MESSAGE, WAIT_SECOND_MESSAGE, SENDING_BIT};
      wait(IRMessagesSendQueue);
      uint16_t dataIn;
      int i;
      int n;
      int w1; // wait time positive
      int w2; // wait time negative

      bool bit; // package
      STATE S = STATE::WAIT_MESSAGE;
        while(true){
          switch(S){
            case STATE::WAIT_MESSAGE:
              wait(IRMessagesSendQueue);
              dataIn = IRMessagesSendQueue.read();
              i = 15;
              n = 0;
              S = STATE::SENDING_BIT;

            case STATE::WAIT_SECOND_MESSAGE:
              SendTimer.set(3000);
              wait(SendTimer);
              S = STATE::SENDING_BIT;
			  
			  
            case STATE::SENDING_BIT:
              bit = (dataIn>>i)& 1;
              if(bit == 1){
                w1 = 1600;
                w2 = 800;
              }else if(bit==0){
                w1 = 800;
                w2 = 1600;
              }
              IrLED.Send(true);
              SendTimer.set(w1);
			  wait(SendTimer);
              IrLED.Send(false);
              SendTimer.set(w2);
			  wait(SendTimer);
              if(i == 0){
                  n++;
                  if(n==2){
                    S = STATE::WAIT_MESSAGE;
                  }else if(n != 2){
                    i = 15;
                    S = STATE::WAIT_SECOND_MESSAGE;
                  }
              }
			  i--;
            }
          }
        }
      };

#endif // SENDIRMESSAGECONTROL_HPP

#ifndef SENDIRMESSAGECONTROL_HPP
#define SENDIRMESSAGECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "IrTransmitter.hpp"

//! \brief Control object that manages the transmitting of ir-messages.
//! \details SendIrMessageControl uses an IrTransmitter to send ir-messages.
//! These messages are given by other classes using the function sendMessage.
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
    //! SendIrMessageControl waiting for a hit to the queue
    //! @param IrTransmitter led that will be toggled
    //! @param low decides the length of the positive low pulse and negative high pulse in microseconds.
    //! @param High decides the length of the positive high pulse and negative low pulse in microseconds.
    //! @param priority gives the task it's priority
    SendIrMessageControl(IrTransmitter & IrLED,
                  uint16_t low,
                  uint16_t high,
                  int priority):
    task(priority, "SendIrMessageControl"), IrLED(IrLED), negHigh(low), negLow(high), posHigh(high), posLow(low), SendTimer( this, "SendTimer" ), IRMessagesSendQueue( this, "IRMessagesSendQueue" ){};



    //! SendIrMessageControl waiting for a hit to the queue
    //! @param IrTransmitter led that will be toggled
    //! @param negLow decides the length of the negative low pulse
    //! @param negHigh decides the length of the negative high pulse
    //! @param posLow decides the length of the positive low pulse
    //! @param posHigh decides the length of the positive high pulse
    //! @param priority gives the task it's priority
    SendIrMessageControl(IrTransmitter & IrLED,
                  uint16_t negLow,
                  uint16_t negHigh,
                  uint16_t posLow,
                  uint16_t posHigh,
                  int priority):
    task(priority, "SendIrMessageControl"),IrLED(IrLED), negHigh(negHigh), negLow(negLow), posHigh(posHigh), posLow(posLow),SendTimer( this, "SendTimer" ), IRMessagesSendQueue( this, "IRMessagesSendQueue" ){};



    //! \brief Sends an ir-message.
	//! @param m This is the encoded message that will be send
    void sendMessage(uint16_t m){
        IRMessagesSendQueue.write(m);
    }

	//! \brief the main() of this task.
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
			  break;

            case STATE::WAIT_SECOND_MESSAGE:
              SendTimer.set(3000);
              wait(SendTimer);
              S = STATE::SENDING_BIT;
			  break;


            case STATE::SENDING_BIT:
              bit = (dataIn>>i)& 1;
              if(bit == 1){
                w1 = posHigh;
                w2 = posLow;
              }else if(bit==0){
                w1 = negHigh;
                w2 = negLow;
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
				  break;
              }
			  i--;
			  break;
            }
          }
        }
      };

#endif // SENDIRMESSAGECONTROL_HPP

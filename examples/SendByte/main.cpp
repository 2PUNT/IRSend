#include "hwlib.hpp"
#include "IrTransmitter.hpp"
#include "SendIrMessageControl.hpp"

class DummySendIrMessageControl: public rtos::task<>{

  private:

    SendIrMessageControl & sirmc;



  public:

    DummySendIrMessageControl(SendIrMessageControl & sirmc):sirmc(sirmc){}

    void main ()override{
      while(true){
        hwlib::wait_ms(2000);
        hwlib::cout << "send to ir";
        sirmc.sendMessage(170); // blink interval
		    hwlib::wait_ms(20000);
      }
    }

};



int main(){
  WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 1000 );

	auto OUT = hwlib::target::d2_36kHz();
  int wait_time = 100;
	IrTransmitter ir(OUT);

  SendIrMessageControl sir(ir, wait_time*20, wait_time*20, 1);

  DummySendIrMessageControl dummytrigger(sir);
  rtos::run();

}

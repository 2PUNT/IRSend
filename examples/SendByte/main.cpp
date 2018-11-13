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
        hwlib::wait_ms(1000);
        //hwlib::cout << "send to ir";
        sirmc.sendMessage(0xB1E3); // blink interval
		
		//id = 10001
		//d  = 00111
		//x  = 10110
		//M  = %1011 0001 1110 0011 = 0xB1E3
      }
    }

};



int main(){
  WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 1000 );

	auto OUT = hwlib::target::d2_36kHz();
  
	IrTransmitter ir(OUT);

  SendIrMessageControl sir(ir, 800, 1600, 1);

  DummySendIrMessageControl dummytrigger(sir);
  rtos::run();

}

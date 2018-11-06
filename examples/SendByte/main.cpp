#include "hwlib.hpp"
#include "IrTransmitter.hpp"
#include "SendIrMessageControl.hpp"

int main(){
  WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 1000 );

	auto OUT = hwlib::target::d2_36kHz();
  int wait_time = 100;
	IrTransmitter ir(OUT);

  SendIrMessageControl sir(ir, wait_time*20, wait_time*20, 1);
  //example sos:
  // 1 2 3 4 5 6 9 10 13 14 17 18 19 20 21
  // ·   ·   ·   —    —     —     ·  ·  ·
  uint16_t oneb = 255;



	for(;;){
    sir.sendMessage(oneb);
  	hwlib::wait_ms( 1000 );
	}
}

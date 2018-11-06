#include "hwlib.hpp"
#include "IrTransmitter.hpp"

void flipWait(IrTransmitter ir, int positive_wait_time, int negative_wait_time ){
    ir.Send(true);
    hwlib::wait_ms(positive_wait_time);
    if(negative_wait_time != 0){
      ir.Send(false);
      hwlib::wait_ms(negative_wait_time);
    }
}

int main(){
  WDT->WDT_MR = WDT_MR_WDDIS;
	hwlib::wait_ms( 1000 );

	auto OUT = hwlib::target::d2_36kHz();
  int wait_time = 100;
	IrTransmitter ir(OUT);

  //example sos:
  // 1 2 3 4 5 6 9 10 13 14 17 18 19 20 21
  // ·   ·   ·   —    —     —     ·  ·  ·

	for(;;){

    flipWait(ir, wait_time, wait_time);
    flipWait(ir, wait_time, wait_time);
    flipWait(ir, wait_time, wait_time);

    flipWait(ir, wait_time*3, wait_time);
    flipWait(ir, wait_time*3, wait_time);
    flipWait(ir, wait_time*3, wait_time);

    flipWait(ir, wait_time, wait_time);
    flipWait(ir, wait_time, wait_time);
    flipWait(ir, wait_time, wait_time);
	}
}

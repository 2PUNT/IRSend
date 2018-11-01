#include "hwlib.hpp"
#include "IrTransmitter.hpp"


int main(){
	
    	WDT->WDT_MR = WDT_MR_WDDIS;	
	hwlib::wait_ms( 1000 );
	
	auto OUT = hwlib::target::d2_36kHz();
	
	IrTransmitter ir(OUT); 

	for(;;){
		ir.Send(false);
	}
}
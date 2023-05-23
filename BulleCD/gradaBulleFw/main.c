/*********************************************************************
 *               dimmer example for Versa1.0
 *	Connect dimmer board to Versa1's VNH2 port.
 *********************************************************************/
#define BOARD Versa2
#include <fruit.h>
#include <dimmer.h>
#include <analog.h>
t_delay mainDelay;

//----------- Setup ----------------
void setup(void) {	
	fruitInit();

	analogInit();
	analogSelect(0,K1);	// assign connector K1 to analog channel 0

	dimmerInit();        // init dimmer module
	delayStart(mainDelay, 20000); 	// init the mainDelay to 20 ms
}

// ---------- Main loop ------------
void loop() {
	fraiseService();// listen to Fraise events
	dimmerService();	// dimmer management routine
	analogService();
	if(delayFinished(mainDelay)) // when mainDelay triggers :
	{
		delayStart(mainDelay, 20000); 	// re-init mainDelay
		//dimmerPrintDebug();
		analogSend();
		//unsigned int i = analogGet(0);
		dimmerSet(0, ((unsigned int)analogGet(0)) << (6 - ANALOG_FILTER));
	}
}

// ---------- Interrupts ------------
void highInterrupts()
{
	dimmerHighInterrupt();
}
void lowInterrupts()
{
	dimmerLowInterrupt();
}

// ---------- Receiving ------------
void fraiseReceive() // receive raw bytes
{
	unsigned char c=fraiseGetChar();
	if(c==40) dimmerReceive(); // if first byte is 40, then call dimmer receive function.
}

/*********************************************************************

*********************************************************************/

#define BOARD Versa2

#include <fruit.h>
#include <switch.h>

t_delay mainDelay;

void setup(void) {	
//----------- Setup ----------------
	fruitInit();
			
	pinModeDigitalOut(LED); 	// set the LED pin mode to digital out
	digitalClear(LED);		// clear the LED
	delayStart(mainDelay, 5000); 	// init the mainDelay to 5 ms

//----------- Switch setup ----------------
	switchInit();
	switchSelect(0,  SW1);
	switchSelect(1,  SW2);
	switchSelect(2,  SW3);
	switchSelect(3,  SW4);
	switchSelect(4,  SW5);
	switchSelect(5,  SW6);
	switchSelect(6,  SW7);
	switchSelect(7,  SW8);
	switchSelect(8,  SW9);
	switchSelect(9,  SW10);
	switchSelect(10, SW11);
	
//----------- LEDs setup ----------------
	pinModeDigitalOut(LED1);
	pinModeDigitalOut(LED2);
	pinModeDigitalOut(LED3);
	pinModeDigitalOut(LED4);
	pinModeDigitalOut(LED5);

	digitalClear(LED1);
	digitalClear(LED2);
	digitalClear(LED3);
	digitalClear(LED4);
	digitalClear(LED5);
}

void loop() {
// ---------- Main loop ------------
	fraiseService();	// listen to Fraise events
	switchService();	// analog management routine

	if(delayFinished(mainDelay)) // when mainDelay triggers :
	{
		delayStart(mainDelay, 5000); 	// re-init mainDelay
		switchSend();		// send analog channels that changed
	}
}

// Receiving

void setLed(byte led, byte v)
{
	switch(led) {
		case 0: digitalWrite(LED1, v != 0); break;
		case 1: digitalWrite(LED2, v != 0); break;
		case 2: digitalWrite(LED3, v != 0); break;
		case 3: digitalWrite(LED4, v != 0); break;
		case 4: digitalWrite(LED5, v != 0); break;
	}
}

void fraiseReceiveChar() // receive text
{
	unsigned char c;
	
	c=fraiseGetChar();
	if(c=='L'){		//switch LED on/off 
		c=fraiseGetChar();
		digitalWrite(LED, c!='0');
	}
	else if(c=='E') { 	// echo text (send it back to host)
		printf("C");
		c = fraiseGetLen(); 			// get length of current packet
		while(c--) printf("%c",fraiseGetChar());// send each received byte
		putchar('\n');				// end of line
	}
	if(c=='l'){		//switch LEDs on/off
		unsigned char led, v;
		led = fraiseGetChar() - '0';
		v = fraiseGetChar() - '0';
		setLed(led, v);
	}
}


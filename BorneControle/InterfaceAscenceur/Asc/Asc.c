/*********************************************************************
 *
 *                Europa / Ascenceur
 *
 *********************************************************************
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Antoine Rousseau  mar 2014     Original.
 ********************************************************************/

/*
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA  02110-1301, USA.
*/

#define BOARD 2X298

#include <core.h>
#include <fraisedevice.h>
#include <eeparams.h>

#include <analog.h>
#include <switch.h>

unsigned char PERIOD=255;
unsigned char t,t2=0;	
#define SET_PWM(pwm,val) do{ CCP##pwm##CONbits.DC##pwm##B1 = val&2;  CCP##pwm##CONbits.DC##pwm##B0 = val&1; CCPR##pwm##L=val>>2; } while(0)

#define	TMR1init(T) (0xffff-((T*FOSC)/32000)) //ms ; maximum: 8MHz:262ms 48MHz:43ms 64MHz:32ms
#define	TMR1initUS(T) (0xffff-((T*FOSC)/32000000)) //us ; 
#define InitTimer(T) do{ TMR1H=TMR1init(T)/256 ; TMR1L=TMR1init(T)%256; PIR1bits.TMR1IF=0; }while(0)
#define InitTimerUS(T) do{ TMR1H=TMR1initUS(T)/256 ; TMR1L=TMR1initUS(T)%256; PIR1bits.TMR1IF=0; }while(0)
#define TimerOut() (PIR1bits.TMR1IF)

unsigned int Leds[8];

#define SETLED(n,p) if(time<Leds[n]) p=1; else p=0;
void UpdateLeds()
{
	//unsigned int time;
	static int time=250;
	
	if(!(time--)) time=500;

	//time=(65535-GetTimer0());
	SETLED(0,MOTA_IN1);
	SETLED(1,MOTA_IN2);
	SETLED(2,MOTB_IN1);
	SETLED(3,MOTB_IN2);
	SETLED(4,MOTC_IN1);
	SETLED(5,MOTC_IN2);
	SETLED(6,MOTD_IN1);
	SETLED(7,MOTD_IN2);
}

void HighInterrupts()
{
	//Servo_ISR();
	if(PIR1bits.TMR1IF) {
		UpdateLeds();
		InitTimerUS(12);//20us free...
	}	
}

void LowInterrupts()
{}

void main(void)
{
	unsigned long t3;//,servoSOF;
	//int tmpint;
	char i;
	
	CoreInit();
		
	for(i=0;i<8;i++) Leds[i]=0;

	MOTC_IN1=0;	
	MOTC_IN2=0;
	MOTD_IN1=0;	
	MOTD_IN2=0;

	MOTA_EN=1;	
	MOTB_EN=1;	
	MOTC_EN=1;	
	MOTD_EN=1;	
	
	SETPORT_MOTA;
	SETPORT_MOTB;
	SETPORT_MOTC;
	SETPORT_MOTD;
	
	//SET_PWM(1,0);
	
#if 0
// --------- init motors PWM on TMR2 -----------
	CCP2CON=CCP1CON=0b00001100 ; // single PWM active high
	T2CONbits.T2CKPS0=1; //prescaler 4
	PR2=255;
	T2CONbits.TMR2ON=1;

#ifndef en_pwm
// ------- init PWM1 to pulse MOTC_IN1
	PSTR1CON=0;
	PSTR1CONbits.STR1D=1;
	PSTR2CON=0;
#else
// ------- init PWM1 to pulse MOTC_EN
	PSTR1CON=0;
	PSTR1CONbits.STR1A=1;
// ------- init PWM2 to pulse MOTD_EN
	PSTR2CON=0;
	PSTR2CONbits.STR2B=1;
#endif

#endif

// -- soft_pwm timer1
	T1CON=0b00110011;//src=fosc/4,ps=8,16bit r/w,on.
	PIE1bits.TMR1IE=1;
	IPR1bits.TMR1IP=1;


// ---------- capture timer : TMR1 ------------
	/*T1CON=0b00110011;//src=fosc/4,ps=8,16bit r/w,on.
	PIE1bits.TMR1IE=1;
	IPR1bits.TMR1IP=1;*/


// ---------- Servos ------------
	//Servo_Init();
	
	//SERVO_SET_PORT(0,K3);

// ---------- Analog ------------
	Analog_Init();
	
//	ANALOG_SELECT(0,K1);
//	ANALOG_SELECT(1,K3);

// ---------- Switchs ------------
	Switch_Init();
	SWITCH_SELECT(0,K1);
	SWITCH_SELECT(1,K2);
	SWITCH_SELECT(2,K4);
	SWITCH_SELECT(3,K5);
	SWITCH_SELECT(4,K6);
	SWITCH_SELECT(5,K8);
	SWITCH_SELECT(6,K10);
	
// ---------- Main loop ------------
	EEreadMain();

	t=PERIOD;
	//servoSOF=
	t3=GetTime();

#define SERVICE(service) do { FraiseService(); service(); } while (0)

	while(1){
		//SERVICE(Analog_Service);
		FraiseService();
		SERVICE(Switch_Service);
		
		if(Elapsed(t3)>Micros(5000UL))
		{
			t3=GetTime();

			//Analog_Send(AMODE_NOSCALE | AMODE_NUM | AMODE_NOCROSS);
			Switch_Send();
			
			if(!t--){
				t=PERIOD;
				//printf("Cs Hello\n");
			}
		}
	}
}

void CharBroadcast()
{
	/*unsigned char c;
	
	printf("Brdcst: ");
	for(c=0;c<FrRXout_len;c++) printf("%c",FrRXgetchar());
	putchar('\n');*/
}

void Broadcast()
{
	/*unsigned char c;
	
	printf("brdcst: ");
	for(c=0;c<FrRXout_len;c++) printf("%d ",FrRXgetchar());
	putchar('\n');*/
}

void CharInput()
{
	unsigned char c;
	
	c=FrRXgetchar();
	//printf("Cchar in:%c %c\n",c,c2);
	if(c=='L'){	
		c=FrRXgetchar();
		/*if(c=='0') 
			{LED=0;}
		else LED=1;*/
	}
	else if(c=='E') {
		printf("C");
		c = FrRXlen();
		while(c--) printf("%c",FrRXgetchar());
		putchar('\n');
	}
	else if(c=='S') { //analog scaling
		c=FrRXgetchar()-'0';
		Analog_Scaling(c!=0);
		if(c==0) EEwriteMain();
	}	
}


void Input()
{
	unsigned char c;//,c2;
	int tmp;
	unsigned int i;
	
	c=FrRXgetchar();

	if((c>=10)&&(c<18)) {
		i=FrRXgetchar()<<8;i+=FrRXgetchar();
		Leds[c-10]=i;
	}
	else switch(c) {
		PARAM_CHAR(1,t2); break;
		PARAM_CHAR(2,PERIOD); break;
		PARAM_INT(3,tmp); SET_PWM(1,tmp); break;
		case 255 : EEwriteMain();break;
	}
}

void EEdeclareMain()
{
	Analog_declareEE();
}

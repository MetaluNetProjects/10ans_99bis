/*********************************************************************
 *
 *                Analog library for Fraise pic18f  device
 *				
 *				
 *********************************************************************
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Antoine Rousseau  march 2013     Original.
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
#ifndef _ANALOG__H_
#define _ANALOG__H_

#ifndef ANALOG_FILTER
#define ANALOG_FILTER 3
#endif

#ifndef ANALOG_THRESHOLD
#define ANALOG_THRESHOLD 7
#endif

#ifndef ANALOG_MINMAX_MARGIN
#define ANALOG_MINMAX_MARGIN 100
#endif

#ifndef ANALOG_SCALED_MAX
#define ANALOG_SCALED_MAX 16383
#endif

#define AMODE_SCALE 1
#define AMODE_NOSCALE 0
#define AMODE_NUM 2
#define AMODE_CHAR 0
#define AMODE_CROSS 4
#define AMODE_NOCROSS 0

void Analog_Init();

void Analog_Select(unsigned char chan,unsigned char hwchan); // attach a hardware channel to a channel

void Analog_Deselect(unsigned char chan); // deselect a channel

void Analog_Service(void); // call often

char Analog_Send(unsigned char mode); // call at the maximum rate you want to report analog ; 
								// if scale==0, send "a val[a]" if channel 'a' changed
								// if scale==1, send "a 4096*( (val[a]-min[a])/(max[a]-min[a]) )
								// return number of channels sent (max 4)

void Analog_Input(unsigned char fraddress);

void Analog_Set(unsigned char chan, int val);
int Analog_GetDist(unsigned char chan);

void Analog_Scaling(unsigned char scaling); // when scaling, min and max are updated each sample

void Analog_declareEE();

void Analog_printmin();
void Analog_printmax();

#define ANALOG_SELECT(num,conn) CALL_FUN2(Analog_Select,num,KAN(conn))


#endif //

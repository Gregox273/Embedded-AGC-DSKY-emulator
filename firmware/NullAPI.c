/*
  Copyright 2004-2005 Ronald S. Burkey <info@sandroid.org>

  This file is part of yaAGC.

  yaAGC is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  yaAGC is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with yaAGC; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  In addition, as a special exception, Ronald S. Burkey gives permission to
  link the code of this program with the Orbiter SDK library (or with
  modified versions of the Orbiter SDK library that use the same license as
  the Orbiter SDK library), and distribute linked combinations including
  the two. You must obey the GNU General Public License in all respects for
  all of the code used other than the Orbiter SDK library. If you modify
  this file, you may extend this exception to your version of the file,
  but you are not obligated to do so. If you do not wish to do so, delete
  this exception statement from your version.

  Filename:	NullAPI.c
  Purpose:	This is sort of a template that shows how to write functions
  		that customize the yaAGC-to-peripheral interface.
		(I advise you not to, unless you are using yaAGC as
		embedded firmware, but I show you how to do it
		anyway.)
  Compiler:	GNU gcc.
  Contact:	Ron Burkey <info@sandroid.org>
  Reference:	http://www.ibiblio.org/apollo/index.html
  Mods:		08/18/04 RSB.	Created.
		02/27/05 RSB	Added the license exception, as required by
				the GPL, for linking to Orbiter SDK libraries.
		05/14/05 RSB	Corrected website references.
		05/31/05 RSB	Added ShiftToDeda.
*/

#ifdef WIN32
typedef unsigned short uint16_t;
#endif
#include "yaAGC.h"
#include "agc_engine.h"
#include "displays.h"
#include "lamps.h"
#include "buttons.h"

#define LAMP_DEFAULT_COLOUR 0x08

//-----------------------------------------------------------------------------
// Any kind of setup needed by your i/o-channel model.

static int ChannelIsSetUp = 0;

static void
ChannelSetup (agc_t *State)
{
  (void)State;
  ChannelIsSetUp = 1;

  // ... anything you like ...

}

/*
 * Convert 7 segment digit state from Apollo representation to DisplayState
 */
static DisplayState convert_to_display_state(const uint8_t digit_bits)
{
  switch(digit_bits&0b11111)
  {
    case(0b10101):
	return N_0;
    case(0b00011):
	return N_1;
    case(0b11001):
	return N_2;
    case(0b11011):
	return N_3;
    case(0b01111):
	return N_4;
    case(0b11110):
	return N_5;
    case(0b11100):
	return N_6;
    case(0b10011):
	return N_7;
    case(0b11101):
	return N_8;
    case(0b11111):
	return N_9;
    default:
	return N_B;
  }
}

static DisplayState convert_pm(uint8_t pm_state)
{
  pm_state &= 0b11;  // Sanitise input

  switch(pm_state)
  {
    case(0b00):
	// Blank
	return N_B;
    case(0b01):
	// +
	return N_P;
    default:
	// -
	return N_M;
  }
}

static void update_channel_0163(int Value)
{
  LampId id;
  for(uint8_t i = 1; i <= 10; i++)
  {
    uint8_t g = LAMP_DEFAULT_COLOUR;
    uint8_t r = LAMP_DEFAULT_COLOUR+3;
    uint8_t b = 0;
    switch(i)
    {
      case(4):
	  id = LAMP_TEMP;
	  break;
      case(5):
	  id = LAMP_KEY_REL;
	  b = LAMP_DEFAULT_COLOUR;  // White lamp
	  break;
      case(6):
	  // Flash VERB/NOUN
	  if(Value & (1<<(i-1)))
	  {
	    displays_set_verb(88);
	    displays_set_noun(88);
	  }
	  else
	  {
	    // Blank VERB
	    displays_set_state_rc(1,5,N_B);
	    displays_set_state_rc(1,6,N_B);
	    // Blank NOUN
	    displays_set_state_rc(2,5,N_B);
	    displays_set_state_rc(2,6,N_B);
	  }
	  continue;
      case(7):
	  id = LAMP_OPR_ERR;
	  b = LAMP_DEFAULT_COLOUR;  // White lamp
	  break;
      case(8):
	  id = LAMP_RESTART;
	  break;
      case(9):
	  id = LAMP_STBY;
	  b = LAMP_DEFAULT_COLOUR;  // White lamp
	  break;
      case(10):
	  //Blank displays
	  if(Value & (1<<(i-1)))
	  {
	    for(int id = 0; id < DISPLAYS_NUM_ROWS * DISPLAYS_NUM_COLS; id++)
	    {
	      displays_set_state_id(id, N_B);
	    }
	  }
	  continue;
      default:
	  continue;
    }

    if(Value & (1<<(i-1)))
    {
      // If ith bit set
      lamps_set_single_quick(id, g, r, b);
    }
    else
    {
      // Clear lamp
      lamps_set_single_quick(id, 0, 0, 0);
    }
  }
}

static void update_channel_010(int Value)
{
  /*
   * State of plus minus symbols
   * In bit order:
   * (MSB)3- 3+ 2- 2+ 1- 1+(LSB)
   */
  static uint8_t pm_state = 0;

  const uint8_t A = Value >> 11;             // Select digit pair (AAAA)
  const uint8_t B = (Value >> 10) & 1;       // Set plus/minus (B)
  const uint8_t C = (Value >> 5) & 0b11111;  // Digit 1 value (CCCCC)
  const uint8_t D = Value & 0b11111;         // Digit 2 value (DDDDD)

  switch(A)
  {
    case(0b1011):
	// Prog
	displays_set_state_rc(0, 5, convert_to_display_state(C));
	displays_set_state_rc(0, 6, convert_to_display_state(D));
	break;
    case(0b1010):
	// Verb
	displays_set_state_rc(1, 5, convert_to_display_state(C));
	displays_set_state_rc(1, 6, convert_to_display_state(D));
	break;
    case(0b1001):
	// Noun
	displays_set_state_rc(2, 5, convert_to_display_state(C));
	displays_set_state_rc(2, 6, convert_to_display_state(D));
	break;
    case(0b1000):
	// Digit 11
	displays_set_state_rc(0, 0, convert_to_display_state(D));
	break;
    case(0b0111):
	// 1+, D12,13
	pm_state ^= (-B ^ pm_state) & (1UL << 0);  // Set 0th bit to B
	displays_set_state_rc(0, 7, convert_pm(pm_state&0b11));
	displays_set_state_rc(0, 1, convert_to_display_state(C));
    	displays_set_state_rc(0, 2, convert_to_display_state(D));
    	break;
    case(0b0110):
	// 1-, D14,15
	pm_state ^= (-B ^ pm_state) & (1UL << 1);  // Set 1st bit to B
	displays_set_state_rc(0, 7, convert_pm(pm_state&0b11));
	displays_set_state_rc(0, 3, convert_to_display_state(C));
    	displays_set_state_rc(0, 4, convert_to_display_state(D));
    	break;
    case(0b0101):
	// 2+, D21,22
	pm_state ^= (-B ^ pm_state) & (1UL << 2);
	displays_set_state_rc(1, 7, convert_pm((pm_state>>2)&0b11));
	displays_set_state_rc(1, 0, convert_to_display_state(C));
    	displays_set_state_rc(1, 1, convert_to_display_state(D));
    	break;
    case(0b0100):
	// 2-, D23,24
	pm_state ^= (-B ^ pm_state) & (1UL << 3);
	displays_set_state_rc(1, 7, convert_pm((pm_state>>2)&0b11));
	displays_set_state_rc(1, 2, convert_to_display_state(C));
    	displays_set_state_rc(1, 3, convert_to_display_state(D));
    	break;
    case(0b0011):
	// D25,31
	displays_set_state_rc(1, 4, convert_to_display_state(C));
	displays_set_state_rc(2, 0, convert_to_display_state(D));
	break;
    case(0b0010):
	// 3+, D32,33
	pm_state ^= (-B ^ pm_state) & (1UL << 4);
	displays_set_state_rc(2, 7, convert_pm((pm_state>>4)&0b11));
	displays_set_state_rc(2, 1, convert_to_display_state(C));
    	displays_set_state_rc(2, 2, convert_to_display_state(D));
    	break;
    case(0b0001):
	// 3-, D34,35
	pm_state ^= (-B ^ pm_state) & (1UL << 5);
	displays_set_state_rc(2, 7, convert_pm((pm_state>>4)&0b11));
	displays_set_state_rc(2, 3, convert_to_display_state(C));
    	displays_set_state_rc(2, 4, convert_to_display_state(D));
    	break;
    case(0b1100):
    {
	// Lamps
	LampId id;
	for(uint8_t i = 1; i <= 9; i++)
	{
	  uint8_t g = LAMP_DEFAULT_COLOUR;
	  uint8_t r = LAMP_DEFAULT_COLOUR+3;
	  uint8_t b = 0;  // Yellow lamp default

	  switch(i)
	  {
	    case(3):
		id = LAMP_VEL;  // Yellow lamp
		break;
	    case(4):
		id = LAMP_NO_ATT;
		b = LAMP_DEFAULT_COLOUR;  // White lamp
		break;
	    case(5):
		id = LAMP_ALT;
		break;
	    case(6):
		id = LAMP_GIMBAL_LOCK;
		break;
	    case(8):
		id = LAMP_TRACKER;
		break;
	    case(9):
		id = LAMP_PROG;
		break;
	    default:
		continue;
	  }

	  if(Value & (1<<(i-1)))
	  {
	    // If ith bit set
	    lamps_set_single_quick(id, g, r, b);
	  }
	  else
	  {
	    // Clear lamp
	    lamps_set_single_quick(id, 0, 0, 0);
	  }
	}
	break;
    }
  }

}

//-----------------------------------------------------------------------------
// The simulated CPU in yaAGC calls this function whenever it wants to write
// output data to an "i/o channel", other than i/o channels 1 and 2, which are
// overlapped with the L and Q central registers.  For example, in an embedded
// design, this would physically control the individual electrical signals
// comprising the i/o port.  In my recommended reference design (see
// SocketAPI.c) data would be streamed out a socket connection from a port.
// In a customized version, FOR EXAMPLE, data might be written to a shared
// memory array, and other execution threads might be woken up to process the
// changed data.

void
ChannelOutput (agc_t * State, int Channel, int Value)
{

  if (!ChannelIsSetUp)
    ChannelSetup (State);

  // ... anything you like ...
  // You don't need to worry about channels 1 and 2 here.

  // By the way, note that some output channels are latched by relays
  // external to the CPU.  For example, 4 bits of the Value of
  // Channel 10 (octal) select one of 16 rows of latches.  Therefore,
  // the 15-bit channel 10 is effectively 16 separate 11-bit registers.
  // You may need to account for this in your model.

  switch(Channel)
  {
    case(7):
	// Some output channels have purposes within the CPU, so we have to
	// account for those separately.
	State->InputChannel[7] = State->OutputChannel7 = (Value & 0160);
	return;
    case(013):
	// Stick data into the RHCCTR registers, if bits 8,9 of channel 013 are set.
	if (0600 == (0600 & Value) && !CmOrLm)
        {
          State->Erasable[0][042] = LastRhcPitch;
          State->Erasable[0][043] = LastRhcYaw;
          State->Erasable[0][044] = LastRhcRoll;
        }
	break;
    case(010):
	// DSKY 7 segment display channel
	update_channel_010(Value);
	break;

    case(011):
    {
	LampId id;
    	for(uint8_t i = 2; i <= 7; i++)
    	{
	  uint8_t g = LAMP_DEFAULT_COLOUR;
	  uint8_t r = LAMP_DEFAULT_COLOUR+3;
	  uint8_t b = 0;

    	  switch(i)
    	  {
    	    case(2):
    		id = LAMP_COMP_ACTY;
    		r = 0; // green lamp
    		break;
    	    case(3):
    		id = LAMP_UPLINK_ACTY;
    		b = LAMP_DEFAULT_COLOUR;  // White lamp
    		break;
//    	    case(4):
//    		id = LAMP_TEMP;
//    	        break;
//    	    case(5):
//    		id = LAMP_KEY_REL;
//    		b = LAMP_DEFAULT_COLOUR;  // White lamp
//    		break;
//    	    case(7):
//		id = LAMP_OPR_ERR;
//    		break;
    	    default:
    		continue;
    	  }

    	  if(Value & (1<<(i-1)))
    	  {
    	    // If ith bit set
    	    lamps_set_single_quick(id, g, r, b);
    	  }
    	  else
    	  {
    	    // Clear lamp
    	    lamps_set_single_quick(id, 0, 0, 0);
    	  }
    	}

    } break;

    case(0163):
	update_channel_0163(Value);
	break;

    default:
      // Do nothing e.g. invalid channel
      return;
  }

}

//----------------------------------------------------------------------
// The simulated CPU in yaAGC calls this function to check for input data
// once for each call to agc_engin.  This input data may be of two kinds:
// 	1. Data available on an "i/o channel"; in this case, a value
//	   of 0 is returned; you can handle as much or as little data
//	   of this kind in any given invocation; or
//	2. A request for an "unprogrammed sequence" to automatically
//	   increment or decrement a counter.  In this case a value of
//	   1 is returned.  The function must return immediately upon
//	   one of these requests, in order ot preserve system timing.
// The former type of data is supposed to be directly written to the
// array State->InputChannel[], while the latter is supposed to call the
// function UnprogrammedIncrement() to handle the actual incrementing.
// ChannelInput() has the responsibility of raising an interrupt-request
// flag (in the array State->InterruptRequests[]) if the i/o channel
// data is supposed to cause an interrupt.  (An example would
// be if the input data represented a DSKY keystroke.)  Interrupt-raising
// due to overflow of counters is handled automatically by the function
// UnprogrammedChannel() and doesn't need to be addressed directly.
//
// For example, in an embedded design, this input data would reflect the
// physical states of individual electrical signals.
// In my recommended reference design (see SocketAPI.c) the data would be
// taken from an incoming stream of a socket connection to a port.
// In a customized version, FOR EXAMPLE, data might indicate changes in a
// shared memory array partially controlled by other execution threads.
//
// Note:  You are guaranteed that yaAGC processes at least one instruction
// between any two calls to ChannelInput.

int
ChannelInput (agc_t *State)
{
  int RetVal = 0;

  if (!ChannelIsSetUp)
    ChannelSetup (State);

  // If there are changes to the input channels, write the data
  // directly to the array State->InputChannel[].  Don't forget to
  // raise a flag in State->InterruptRequests if the incoming data
  // is supposed to do that.  (Mainly, DSKY keystrokes.)

  // If the inputs request unprogrammed counter-increment sequences,
  // then call the function UnprogrammedChannel(State,Counter,IncType)
  // to process them.  The different unprogrammed sequences are
  // related to the IncTypes as follows:
  //	PINC	000
  //	PCDU	001
  //	MINC	002
  //	MCDU	003
  //	DINC	004
  //	SHINC	005
  //	SHANC	006
  // (Refer to the developer page on www.ibiblio.org/apollo/index.html.)
  // Only registers 32 (octal) through 60 (octal) may actually used as
  // counters, and not all of them.  (Refer to the AGC assembly-language
  // manual at www.ibiblio.org/apollo/index.html.)

  /*
   * Channel 015
   */
  if(button_pressed != NUM_BUTTONS)
  {
    // A button has been pressed
    uint8_t keycode;
    switch(button_pressed)
    {
      case(BUTTON_0):
	  keycode = 16;
	  break;
      case(BUTTON_1):
	  keycode = 1;
	  break;
      case(BUTTON_2):
	  keycode = 2;
	  break;
      case(BUTTON_3):
	  keycode = 3;
	  break;
      case(BUTTON_4):
	  keycode = 4;
	  break;
      case(BUTTON_5):
	  keycode = 5;
	  break;
      case(BUTTON_6):
	  keycode = 6;
	  break;
      case(BUTTON_7):
	  keycode = 7;
	  break;
      case(BUTTON_8):
	  keycode = 8;
	  break;
      case(BUTTON_9):
	  keycode = 9;
	  break;
      case(BUTTON_VERB):
	  keycode = 17;
	  break;
      case(BUTTON_RSET):
	  keycode = 18;
	  break;
      case(BUTTON_KEY_REL):
	  keycode = 25;
	  break;
      case(BUTTON_PLUS):
	  keycode = 26;
	  break;
      case(BUTTON_MINUS):
	  keycode = 27;
	  break;
      case(BUTTON_ENTR):
	  keycode = 28;
	  break;
      case(BUTTON_CLR):
	  keycode = 30;
	  break;
      case(BUTTON_NOUN):
	  keycode = 31;
	  break;
      default:
	// Invalid value
	button_pressed = NUM_BUTTONS;  // Reset flag
	return RetVal;
    }
    State->InputChannel[015] &= ~(0b11111);  // Clear previous keycode
    State->InputChannel[015] |= keycode;
//    int val = ReadIO(State, 015) | keycode;
//    WriteIO(State, 015, val);
    State->InterruptRequests[5] = 1;

    button_pressed = NUM_BUTTONS;  // Reset flag
  }

  /*
   * Channel 032
   */
  if(buttons_get_state_id(BUTTON_PRO))
    State->InputChannel[032] &= ~(1UL << 13);  // Clear bit 14
  else
    State->InputChannel[032] |= 1U << 13;  // Set bit 14


  return (RetVal);
}

//----------------------------------------------------------------------
// A function for handling anything routinely needed (i.e., executed on
// a regular schedule) by the i/o channel model of ChannelInput and
// ChannelOutput.  There are no good reasons that I know of why this
// would be needed, other than by my reference model (see SocketAPI.c),
// so you might just want to let this empty.

void
ChannelRoutine (agc_t *State)
{

  if (!ChannelIsSetUp)
    ChannelSetup (State);

  // ... anything you like ...

}

//----------------------------------------------------------------------
// This function is useful only for debugging the socket interface, and
// so can be left as-is.

void
ShiftToDeda (agc_t *State, int Data)
{
  (void)State;
  (void)Data;
}



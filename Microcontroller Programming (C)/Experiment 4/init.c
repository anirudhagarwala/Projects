/**
	@author Thomas Grunenberg
	@author Anirudh Agarwala
	@version 0.1
	@file init.c
	@brief Init function for the I/O
*/


/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include "init.h"
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Init the PORTx and DDRx register for the I/O setup
*/
void init(void){
	
	// Digital input
	DDRB &= ~(1 << DDB0);		// PB0 as Input
	DDRB &= ~(1 << DDB1);		// PB1 as Input
	PORTB |= ( 1 << PB0);		// Pullup PB0
	PORTB |= ( 1 << PB1);		// Pullup PB1
	
	// Digital output
	DDRC |= (1 << DDC0);		// PC0 as output
	PORTC &= ~( 1 << PC0);		// Port value off	

}
/******************************************************************************/

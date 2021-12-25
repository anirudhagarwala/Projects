
//      This program is free software; you can redistribute it and/or modify
//      it under the terms of the GNU General Public License as published by
//      the Free Software Foundation; either version 2 of the License, or
//      (at your option) any later version.
//      
//      This program is distributed in the hope that it will be useful,
//      but WITHOUT ANY WARRANTY; without even the implied warranty of
//      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//      GNU General Public License for more details.
//      
//      You should have received a copy of the GNU General Public License
//      along with this program; if not, write to the Free Software
//      Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
//      MA 02110-1301, USA.
// 

    
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
	

}
/******************************************************************************/

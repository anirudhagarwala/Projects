/**
	@author Thomas Grunenberg
	@author Anirudh Agarwala
	@version 0.1
	@file i2c_master.c
	@brief Use the Two Wire Interface / I2C
*/



/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <avr/io.h>
#include <util/twi.h>
#include "i2c_master.h"

/******************************************************************************/

/******************************************************************************/
/* INTERNAL FUNCTIONS                                                         */
/******************************************************************************/

/**
	@brief Open a connection for access
	@param adr adress to open
	@return 0: no error, 1: bus error, 2: no answer
*/
uint8_t i2c_master_open_raw(uint8_t adr){
	
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN); // Send START condition
	while( !( TWCR & (1 << TWINT) ) ) // wait until this is done
		;
	
	// Check value of TWSR
	if ( (TWSR & 0xF8) != TW_START && (TWSR & 0xF8) != TW_REP_START)
		return 1;

	// slave address to bus and wait until this is donde
	TWDR = adr;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while( !( TWCR & ( 1 << TWINT) ) )
		;

	// check value (masked prescaler bits)
	if ( (TWSR & 0xF8) == TW_MT_SLA_ACK ) 
		return 0;
	if ( (TWSR & 0xF8) == TW_MR_SLA_ACK ) 
		return 0;

	// If here no Slave: error
	return 2;

}
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Init                                                                       */
/*----------------------------------------------------------------------------*/

void i2c_master_init(uint8_t pullups, uint8_t prescaler){
	
	
	if (prescaler < 11) // prescalrer must be bigger than 10, see datasheet
		prescaler = 11;
	
	// TWI Ports	
	DDRC &= ~(1 << PC5);
	DDRC &= ~(1 << PC4);
	if (pullups){
		PORTC |= (1 << PC5);
		PORTC |= (1 << PC4);
	} else {
		PORTC &= ~(1 << PC5);
		PORTC &= ~(1 << PC4);	
	
	}

	//TWI
	TWBR = prescaler;
	TWSR = (1<<TWPS0); //Prescalar 4
}
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Write access to slave                                                      */
/*----------------------------------------------------------------------------*/


uint8_t i2c_master_open_write(uint8_t adr){
	
	// Make sure, that the last bit is zero (for write)
	return i2c_master_open_raw(adr & 0xFE);
}
/******************************************************************************/

uint8_t i2c_master_write(uint8_t towrite){	
    
	// send data to the already open device
	TWDR = towrite;
	TWCR = (1<<TWINT) | (1<<TWEN);

	// wait until transmission completed
	while( !( TWCR & (1 << TWINT) ) )
		;

	// check value of TWI Status Register. Check for ACK
	if( (TW_STATUS & 0xF8) != TW_MT_DATA_ACK)
		return 1;
	
	// If no error, return zero
	return 0;

}
/******************************************************************************/


/*----------------------------------------------------------------------------*/
/* Read access to slave                                                       */
/*----------------------------------------------------------------------------*/

uint8_t i2c_master_open_read(uint8_t adr){
	
	// Make sure, that the last bit is one (for read)
	return i2c_master_open_raw(adr | 0x01);

}
/******************************************************************************/

uint8_t i2c_master_read_next(void){

	// Enable reciving 
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);

	// wait for complete byte
	while( !( TWCR & (1 << TWINT) ) )
		;    

    return TWDR;
}
/******************************************************************************/

uint8_t i2c_master_read_last(void){
	
	
	// Enable reciving (with stop condition)
	TWCR = (1<<TWINT) | (1<<TWEN); //TWEA bit is set 0 because it is last bit
	// TODO
		
	// wait for complete byte
	while( !( TWCR & (1 << TWINT) ) )
		;
	
    return TWDR;

}
/******************************************************************************/

/*----------------------------------------------------------------------------*/
/* Close a data transfer                                                      */
/*----------------------------------------------------------------------------*/

void i2c_master_close(){
	
    // send stop
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO); //TWSTO set to 1 to send a stop signal
	// TODO
	
	// wait until this is done
	while( TWCR & (1 << TWSTO) )
		;

}
/******************************************************************************/



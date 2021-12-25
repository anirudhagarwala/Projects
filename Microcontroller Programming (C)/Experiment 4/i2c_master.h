/**
	@author Thomas Grunenberg
	@author TODO
	@version 0.1
	@file ds1307.h
	@brief Use TWI / I2C in master mode
*/


#ifndef I2C_MASTER_H
#define I2C_MASTER_H


#include <avr/io.h>



/*----------------------------------------------------------------------------*/
/* Init                                                                       */
/*----------------------------------------------------------------------------*/

/**
	@brief Init the I2C interface
*/
void i2c_master_init(uint8_t pullups, uint8_t prescaler);


/*----------------------------------------------------------------------------*/
/* Write access to slave                                                      */
/*----------------------------------------------------------------------------*/

/**
	@brief Open a connection for write access
	@param adr adress to open, the last bit should be zero
	@return 0: no error, 1: bus error, 2: no answer
*/
uint8_t i2c_master_open_write(uint8_t adr);

/**
	@brief Write a byte to the slave
	@param towrite byte to write
	@return 0: no error, 1: got no ACK
*/
uint8_t i2c_master_write(uint8_t towrite);

/*----------------------------------------------------------------------------*/
/* Read access to slave                                                       */
/*----------------------------------------------------------------------------*/

/**
	@brief Open a connection for read access
	@param adr adress to open, the last bit will be ignored/overwritten
	@return 0: no error, 1: bus error, 2: no answer
*/
uint8_t i2c_master_open_read(uint8_t adr);


/**
	@brief Read a byte from the slave (and after that more bytes)
	@return received byte
*/
uint8_t i2c_master_read_next(void);

/**
	@brief Read a byte from the slave (and after that no more bytes)
	@return received byte
*/
uint8_t i2c_master_read_last(void);



/*----------------------------------------------------------------------------*/
/* Close a data transfer                                                      */
/*----------------------------------------------------------------------------*/

/**
	@brief Stop the current I2C data transfer / Close connection
*/
void i2c_master_close();






#endif


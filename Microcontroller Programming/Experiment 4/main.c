/**
	@author Thomas Grunenberg
	@author Anirudh Agarwala
	@version 0.1
	@file main.c
	@brief Main programm for external DS1307
*/

const char MtrNum[] __attribute__((__progmem__)) = "27844";

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL

/**
	@brief I2C Address of the DS1307
*/
#define DS1307_I2C_ADR 0xD0 //TODO: Enter the Address of the DS1307 = 1101000 0/1

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c_master.h"
#include "init.h"
#include "lcd.h"
/******************************************************************************/


/******************************************************************************/
/* GLOBAL MEMORY                                                              */
/******************************************************************************/
char* dayofweek[8] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun", "Err"};

// Global Time memory
uint8_t second;
uint8_t minute;
uint8_t hour;
uint8_t day;
uint8_t month;
uint8_t year;
uint8_t weekday;

/******************************************************************************/



/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

/**
	@brief Convert from BCD to Binary
	@param in BCD input (00-99)
	@return Binary output
*/
uint8_t ds1307_decodeBcd(uint8_t in){
	// TODO
	return (((in>>4)*10) + (in&0xF));
}
/******************************************************************************/

/**
	@brief Convert from Binary to BCD
	@param in Binary input (0-99)
	@return BCD output
*/
uint8_t ds1307_encodeBcd(uint8_t in){
	return ((in / 10) << 4 ) | (in % 10); 
}
/******************************************************************************/


/**
	@brief Show time/date with the LCD
*/
void display_showtime(void){
	char str[16];
	
	// Time and Year
	snprintf(str, 16, "%02d:%02d:%02d  20%02d", hour, minute,
			second, year);
	
	lcd_clear();
	lcd_string(str);
	
	
	// Date and Weekday
	if (weekday < 9 && weekday > 0 ){
		snprintf(str, 16, "%02d.%02d  %s", day, month,
			dayofweek[weekday - 1 ]);
	} else {
		snprintf(str, 16, "Error");
	}
	
	lcd_setcursor(0,2);
	lcd_string(str);

	return;
}
/******************************************************************************/

/**
	@brief Write a row byte to the DS1307
	@param adr address to write
	@param data byte to write
*/
void ds1307_write(uint8_t adr, uint8_t data){
	
	if (i2c_master_open_write(DS1307_I2C_ADR))
		return;
	
	i2c_master_write(adr);
	i2c_master_write(data);
	
	i2c_master_close();
}
/******************************************************************************/

/**
	@brief Read a row byte from the DS1307
	@param adr address to read
	@return the received byte
*/
uint8_t ds1307_read(uint8_t adr){
	uint8_t ret;

	if (i2c_master_open_write(DS1307_I2C_ADR))
		return 0;
	
	i2c_master_write(adr);
	i2c_master_open_read(DS1307_I2C_ADR);
	ret = i2c_master_read_last();
	
	i2c_master_close();

	return ret;

}
/******************************************************************************/

/**
	@brief Start or freeze the clock of the DS1307
	@param run zero for stop, all other for run
*/
void ds1307_rtc(uint8_t run){
	
	uint8_t readout;
	
	// Read current value
	readout = ds1307_read(0x00);
	
	
	// Set CH bit
	if (run)
		readout &= ~(0x80);
	else
		readout |= 0x80;
		
	// Write value back
	ds1307_write(0x00, readout);
}
/******************************************************************************/

/**
	@brief Write the current time to the DS1307
	@return zero for no error, one for communication error
*/
uint8_t ds1307_setTime(void){
	uint8_t chbit = ds1307_read(0x00) & 0x80;

	// Open device for write
	if (i2c_master_open_write(DS1307_I2C_ADR))
		return 1;

	i2c_master_write(0x00);
	if (chbit)
		i2c_master_write(ds1307_encodeBcd(second) | 0x80);
	else
		i2c_master_write(ds1307_encodeBcd(second) & 0x7F);		
	
	i2c_master_write(ds1307_encodeBcd(minute));
	i2c_master_write(ds1307_encodeBcd(hour));
	
	i2c_master_write(weekday);		
	
	i2c_master_write(ds1307_encodeBcd(day));
	i2c_master_write(ds1307_encodeBcd(month));
	i2c_master_write(ds1307_encodeBcd(year));		
	
	
	// Close I2C bus
	i2c_master_close();
	
	return 0;
}
/******************************************************************************/

/**
	@brief Get the current time from the DS1307
	@return zero for no error, one for communication error
*/
uint8_t ds1307_getTime(void){

	// Open device for write
	if (i2c_master_open_write(DS1307_I2C_ADR))
		return 1;
	
	// select reading position (0x00)
	i2c_master_write(0x00);
	
	// (Re-)Open device for read
	i2c_master_open_read(DS1307_I2C_ADR);
	
	// Read value
	second = ds1307_decodeBcd(i2c_master_read_next() & 0x7F);
	// TODO minute, hour, ...
	minute = ds1307_decodeBcd(i2c_master_read_next());
	hour = ds1307_decodeBcd(i2c_master_read_next() & 0xBF);
	weekday = ds1307_decodeBcd(i2c_master_read_next());
	day = ds1307_decodeBcd(i2c_master_read_next());
	month = ds1307_decodeBcd(i2c_master_read_next());
	year = ds1307_decodeBcd(i2c_master_read_last());
	
	// Close I2C bus
	i2c_master_close();
	
	return 0;
}
/******************************************************************************/

/**
	@brief Set the time to the "default" time
*/
void ds1307_SetToDefaultTime(void){

	// Defined start time
	second = 55;
	minute = 59;
	hour = 23;
	day = 31;
	month = 12;
	year = 20;
	weekday = 4;
	//TODO: Write this time to the DS1307
	i2c_master_open_write(DS1307_I2C_ADR);
	i2c_master_write(0x00);
	i2c_master_write(ds1307_encodeBcd(second) & 0x7F);		
	i2c_master_write(ds1307_encodeBcd(minute));
	i2c_master_write(ds1307_encodeBcd(hour));
	
	i2c_master_write(weekday);		
	
	i2c_master_write(ds1307_encodeBcd(day));
	i2c_master_write(ds1307_encodeBcd(month));
	i2c_master_write(ds1307_encodeBcd(year));	
	// Close I2C bus
	i2c_master_close();
	
	
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/
int main(void){
	uint8_t running = 1;
	init(); 	// Function to initialise I/Os
	lcd_init(); // Function to initialise LCD display
	i2c_master_init(1, 10); // Init TWI
	ds1307_rtc(running);

	// Loop forever
	while (1){
		
		// Short delay----------------------------------------------------------
		_delay_ms(100);
		
		// Load current time/date from DS1307-----------------------------------
		ds1307_getTime();
		
		// Show current time/date-----------------------------------------------
		// TODO
		display_showtime();
		
	
		// PB0 to toggle run----------------------------------------------------
		if ( ~PINB & (1 << PB0) ){

			if (running)
				running = 0;
			else
				running = 1;
		
			ds1307_rtc(running);		
		
			// Debouncing
			_delay_ms(50);
			while ( ~PINB & (1 << PB0) )
				;
			_delay_ms(50);
		}	
		
		// PB1 set to default time----------------------------------------------
		if ( ~PINB & (1 << PB1) ){
			ds1307_SetToDefaultTime();
			
			// Debouncing
			_delay_ms(50);
			while ( ~PINB & (1 << PB0) )
				;
			_delay_ms(50);			
			
		}
	}

	return 0;
}
/******************************************************************************/

/**
	@author Thomas Grunenberg
	@author Anirudh Agarwala
	@version 0.1
	@file main.c
	@brief Main programm for temperature data logger
*/

const char MtrNum[] __attribute__((__progmem__)) = "27844";

/**
	@brief The CPU speed in Hz
*/
#define F_CPU 8000000UL


#define TEMPSENOR_OFFSET -800 // TODO (DONE)

/**
	@brief I2C Address of the DS1307
*/
#define DS1307_I2C_ADR 0xD0 //(DONE) TODO: Enter the Address of the DS1307 : 11010000
#define ADR_EEPROM 0xA2 //EEPROM Address

/******************************************************************************/
/* INCLUDED FILES                                                             */
/******************************************************************************/
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#include "i2c_master.h"
#include "init.h"
#include "lcd.h"
#include "stdio.h"
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
	//(DONE) TODO
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
	@brief Show time/date/temperature with the LCD
*/

void display_standby(uint16_t t){
	char str[16];
	
	// Time and Year
	snprintf(str, 16, "%02d:%02d:%02d  20%02d", hour, minute, second, year);
	
	lcd_clear();
	lcd_string(str);
	
	
	// Date and Temperature
	snprintf(str, 16, "%02d.%02d  %d.%d C", day, month, t/10, t%10);
	
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
	//(DONE) TODO minute, hour, ...
	minute = ds1307_decodeBcd(i2c_master_read_next());
	hour = ds1307_decodeBcd(i2c_master_read_next() & 0x3F);
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
	@brief Get next time (+10 seconds) 
	@return -
*/

void nexttime(void){
	if (second>=50)
	{
		second = second%10;
		minute++;
	} else {
		second = second + 10;
	}
	if (minute>59)
	{
		minute = 0;
		hour++;
	}
}
/******************************************************************************/


/**
	@brief Load 8 bit value from the EEPROM
	@return loaded value
*/

uint8_t load_value8bit(uint8_t pos){
	uint8_t value;
	/* TODO (DONE)*/ 
	i2c_master_open_write(ADR_EEPROM);
	i2c_master_write(pos);
	i2c_master_open_read(ADR_EEPROM);
	value = i2c_master_read_last();
	i2c_master_close();
	return value;
}
/******************************************************************************/


/**
	@brief Load a 16 bit value from the EEPROM
	@return loaded value
*/

uint16_t load_value16bit(uint8_t pos){
	uint8_t highbyte, lowbyte;
	/* TODO (DONE)*/
	i2c_master_open_write(ADR_EEPROM);
	i2c_master_write(pos);
	i2c_master_open_read(ADR_EEPROM);
	highbyte = i2c_master_read_next();
	lowbyte = i2c_master_read_last();
	i2c_master_close();
	return highbyte * 256 + lowbyte;
}
/******************************************************************************/

/**
	@brief Save a 8 bit value to the EEPROM
	@param tosave value to save
*/

void save_value8bit(uint8_t tosave, uint8_t pos){

	/* TODO (DONE)*/
	
	i2c_master_open_write(ADR_EEPROM);
	i2c_master_write(pos);
	i2c_master_write(tosave);

	i2c_master_close();
	_delay_ms(10); // wait 10ms to make sure that data is written
}
/******************************************************************************/


/**
	@brief Save a 16 bit value to the EEPROM
	@param tosave value to save
*/

void save_value16bit(uint16_t tosave, uint8_t pos){
	uint8_t highbyte, lowbyte;
	highbyte = tosave/256;
	lowbyte = tosave%256;
	i2c_master_open_write(ADR_EEPROM);
	i2c_master_write(pos);
	i2c_master_write(highbyte);	
	i2c_master_write(lowbyte);
	
	i2c_master_close();
	_delay_ms(10); // wait 10ms to make sure that data is written	
}
/******************************************************************************/


/**
	@brief Read the temperature with the internal analog sensor
	@return temperature in 1/10 deg. Celsius
*/

uint16_t adc_temperature_oversample(void){
	uint8_t i;
	uint32_t sum = 0;
	
	for (i = 0; i < 128; i++){
		ADCSRA |= (1 << ADSC)| (1 << ADEN); // Start ADC
	
		while( ADCSRA & (1 << ADSC) ) // wait for ADC complete
			;
	
		sum += ADCW;
	}

	sum /= 128;
	sum /= 32;
	
	// substract offset
	sum = sum - TEMPSENOR_OFFSET;

	// 0.27 deg. Celsius per step
	sum *= 27;
	sum /= 100;
	
	return sum;
}
/******************************************************************************/


/**
	@brief Check if EEPROM has previously stored temperature data
	@return 1 if there is data, 0 if there is no data
*/

uint8_t check_memory(){ 
	uint8_t currentbyte;
	uint8_t check = 1;
	int i;
	
	for (i = 0; i < 256; i++)
	{
		currentbyte = load_value8bit(i);
		if (currentbyte != 0)
		{
			check = 0;
			break;
		}
	}
	
	return check;	
}
/******************************************************************************/


/**
	@brief Clear data from EEPROM
	@return -
*/

void clear_memory(){
	int i;
	
	for (i = 0; i < 256; i++)
	{
		save_value8bit(0, i);
	}
	
	lcd_clear();
	lcd_string("Memory Cleared");
	_delay_ms(1000);
}
/******************************************************************************/


/**
	@brief Check time gap of 10 seconds
	@return 1 if less than 10 seconds, 0 if crossed 10 seconds
*/

uint8_t saving_screen_check(uint8_t recorded_sec, uint8_t recorded_min) //To check 10 second gap
{
		if ((second<(recorded_sec+10))&&(minute==recorded_min)) {return 1;}
		else if((minute==(recorded_min+1)) && ((second%10) < (recorded_sec%10))) {return 1;}
		else{return 0;}
}
/******************************************************************************/


/**
	@brief Store data/check if eeprom empty on pressing PB0
	@return -
*/

void log_data(void){
	// TODO (DONE)
	if (!check_memory()) 
	{
		lcd_clear();
		lcd_string("Memory not empty");
		_delay_ms(1000);
		return;
	}
	
	//SAVE VALUES
	save_value8bit(year, 1);
	save_value8bit(month, 2);
	save_value8bit(day, 3);
	save_value8bit(hour, 4);
	save_value8bit(minute, 5);
	save_value8bit(second, 6);
	
	uint8_t num;
	uint16_t temp;
	uint8_t recorded_min = minute;
	uint8_t recorded_sec = second;
	char str[16];

	_delay_ms(1000); 
	for (num = 1; num <= 124; num++)
	{
		recorded_min = minute;
		recorded_sec = second;
		temp = adc_temperature_oversample(); 		
		save_value16bit(temp, 2*(num-1)+7);
		save_value8bit(num, 0);
		
		while(saving_screen_check(recorded_sec, recorded_min))		//Checking 10 seconds gap
		{
			_delay_ms(100);
			temp = adc_temperature_oversample(); 
			lcd_clear();
			lcd_string("Recording Data");
			lcd_setcursor(0,2);
			snprintf(str, 16, "n: %d, %d.%d C", num, temp/10, temp%10);
			lcd_string(str);			
			
			if (~PINB & (1 << PB0) && ~PINB & (1 << PB1))	//when both buttons are pressed, stop recording
			{
				lcd_clear();
				lcd_string("Recording Stop");
				_delay_ms(1000);
				return;
			}
			
			ds1307_getTime();
		}
		
	} 
	
	lcd_clear(); //If prematurely not stopped, memory full at n = 124 (breaking out of for loop)
	lcd_string("Memory is full!");
	_delay_ms(1000);
	
	return;
}
/******************************************************************************/


/**
	@brief Show data on pressing PB1
	@return -
*/

void show_data(void){
	
	while (~PINB & (1 << PB0)) //Wait for releasing PB0
		;
	_delay_ms(50);
	
	// TODO (DONE)
	if (check_memory())
	{
		lcd_clear();
		lcd_string("Memory Empty");
		_delay_ms(1000);
		return;
	}
	char str[16];
	uint8_t num = load_value8bit(0);		
	
	uint8_t check_read = 0;
	
	while(1)						//until the button is pressed again
	{
		_delay_ms(100);
		lcd_clear();								 
		snprintf(str, 16, "Recording = %03d ", num); //Number of temperatures
		lcd_string(str);
		lcd_setcursor(0,2);
		ds1307_getTime();
		snprintf(str, 16, "%02d:%02d:%02d-%02d.%d C", hour, minute, second, adc_temperature_oversample()/10, adc_temperature_oversample()%10); //Current (running) time and temperature
		lcd_string(str);
		
		if (~PINB & (1 << PB0) || ~PINB & (1 << PB1))	//check if either of the buttons are pressed
		{
			_delay_ms(50);
			
			if (~PINB & (1 << PB0)) //If button 1 (read) is pressed, go out of the loop
			{
				check_read = 1;
			}
			
			while (~PINB & (1 << PB0) || ~PINB & (1 << PB1)) //Check if again either of the buttons were pressed
			{
				if (~PINB & (1 << PB0) && ~PINB & (1 << PB1)) //If both buttons pressed, clear data and return
				{
					clear_memory();
					while (~PINB & (1 << PB0) && ~PINB & (1 << PB1))
						;
					_delay_ms(50);
					
					return;
				}
			}
			
			if (check_read == 1) //If both buttons not pressed, and just button 1 is pressed, finally break out of the loop
			{
				_delay_ms(50);	//debouncing
				check_read = 0;
				break;	
			}				
			
		}
	
	}
	
	//Loading data from Memory
	year = load_value8bit(1);
	month = load_value8bit(2);
	day = load_value8bit(3);
	hour = load_value8bit(4);
	minute = load_value8bit(5);
	second = load_value8bit(6);
	
	uint16_t temp;
	int i = 1;	
	while(1)
	{
		_delay_ms(100);
		
		temp = load_value16bit(2*(i-1)+7);
		
		lcd_clear();
		snprintf(str, 16, "Temp: %d.%d C", temp/10, temp%10); //Temperature display
		lcd_string(str);
		lcd_setcursor(0,2);
		snprintf(str, 16, "Time: %02d:%02d:%02d", hour, minute, second); //Time at which temp stored display
		lcd_string(str);
		
		
		if (~PINB & (1 << PB0) || ~PINB & (1 << PB1))
		{
			_delay_ms(50);
			
			if (~PINB & (1 << PB0)) //If button 1 (read) is pressed, go to next value
			{
				check_read = 1;
			}
			
			while (~PINB & (1 << PB0) || ~PINB & (1 << PB1)) //Check again if either of the buttons were pressed
			{
				if (~PINB & (1 << PB0) && ~PINB & (1 << PB1)) //If both buttons pressed, clear data and return
				{
					clear_memory();
					while (~PINB & (1 << PB0) && ~PINB & (1 << PB1))
						;
					_delay_ms(50);
					return;
				}
			}
			
			if (check_read == 1)	//if button 1 is pressed again, show next value
			{
				_delay_ms(50);
				
				if (i == num)		//if last value return to main screen
					return;
				
				i++;
				nexttime();
			}
		}
		
	}
}
/******************************************************************************/


/**
	@brief Main function
	@return only a dummy to avoid a compiler warning, not used
*/

int main(void){
	uint16_t nowtemp;

	init(); 	// Function to initialise I/Os
	lcd_init(); // Function to initialise LCD display
	i2c_master_init(1, 10); // Init TWI


	// Analog Input
	//(DONE) TODO
	ADMUX |= (1 << REFS1) | (1 << REFS0); // 1.1V as reference
	ADCSRA = (1 << ADPS2)| (1 << ADPS1); // ADC Prescale by 64
	ADCSRA |= (1 << ADSC)| (1 << ADEN); // Start first conversion (dummy read)

	// Loop forever
	for(;;){
		
		// Short delay
		_delay_ms(100);
		
		
		// Mesure temperature
		nowtemp = adc_temperature_oversample();
		
		
		// Load current time/date from DS1307
		//(DONE) TODO
		ds1307_getTime();
		
		// Show current time/date
		display_standby(nowtemp);

		// Show recorded data
		if ( ~PINB & (1 << PB0) )
			show_data();
		
		// Start Recording
		if (~PINB & (1 << PB1))
			log_data();

	}

	return 0;
}
/******************************************************************************/

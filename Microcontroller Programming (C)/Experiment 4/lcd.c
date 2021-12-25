// control a HD44780 compatible LCD in 4-Bit-Interfacemode


 
#include <avr/io.h>
#include "lcd.h"
#include <util/delay.h>
 
////////////////////////////////////////////////////////////////////////////////
// Generate a Enable-Puls
static void lcd_enable( void )
{
    LCD_PORT |= (1<<LCD_EN);     // Enable auf 1 setzen
    _delay_us( LCD_ENABLE_US );  // kurze Pause
    LCD_PORT &= ~(1<<LCD_EN);    // Enable auf 0 setzen
}
 
////////////////////////////////////////////////////////////////////////////////
// Send 4-bit output operation to LCD
static void lcd_out( uint8_t data )
{
    data &= 0xF0;                       // mask highnibble
 
    LCD_PORT &= ~(0xF0>>(4-LCD_DB));    // delete mask
    LCD_PORT |= (data>>(4-LCD_DB));     // set Bits 
    lcd_enable();
}
 
////////////////////////////////////////////////////////////////////////////////
// Initialialise
void lcd_init( void )
{
    // switch used Pins to output mode
    uint8_t pins = (0x0F << LCD_DB) |           // 4 Datalines
                   (1<<LCD_RS) |                // R/S Line
                   (1<<LCD_EN);                 // Enable line
    LCD_DDR |= pins;
 
    // all outputs to zero
    LCD_PORT &= ~pins;
 
    // wait for the LCD to be ready
    _delay_ms( LCD_BOOTUP_MS );
    
    // send Soft-Reset 
    lcd_out( LCD_SOFT_RESET );
    _delay_ms( LCD_SOFT_RESET_MS1 );
 
    lcd_enable();
    _delay_ms( LCD_SOFT_RESET_MS2 );
 
    lcd_enable();
    _delay_ms( LCD_SOFT_RESET_MS3 );
 
    // activate 4-bit Mode  
    lcd_out( LCD_SET_FUNCTION |
             LCD_FUNCTION_4BIT );
    _delay_ms( LCD_SET_4BITMODE_MS );
 
    // 4-bit Mode / 2 lines / 5x7
    lcd_command( LCD_SET_FUNCTION |
                 LCD_FUNCTION_4BIT |
                 LCD_FUNCTION_2LINE |
                 LCD_FUNCTION_5X7 );
 
    // Display on / Cursor off / Blink off
    lcd_command( LCD_SET_DISPLAY |
                 LCD_DISPLAY_ON |
                 LCD_CURSOR_OFF |
                 LCD_BLINKING_OFF); 
 
    // Cursor inkrement / no Scrolling
    lcd_command( LCD_SET_ENTRY |
                 LCD_ENTRY_INCREASE |
                 LCD_ENTRY_NOSHIFT );
 
    lcd_clear();
}
  
////////////////////////////////////////////////////////////////////////////////
// Send Databyte to LCD
void lcd_data( uint8_t data )
{
    LCD_PORT |= (1<<LCD_RS);    // set RS to 1
 
    lcd_out( data );            // first the higher.., 
    lcd_out( data<<4 );         // then the lower nibble
 
    _delay_us( LCD_WRITEDATA_US );
}
 
////////////////////////////////////////////////////////////////////////////////
// Send a comand to the LCD
void lcd_command( uint8_t data )
{
    LCD_PORT &= ~(1<<LCD_RS);    // set RS to 0 s
 
    lcd_out( data );             // first the higher..., 
    lcd_out( data<<4 );           // then the lower nibble
 
    _delay_us( LCD_COMMAND_US );
}
 
////////////////////////////////////////////////////////////////////////////////
// Send clear command
void lcd_clear( void )
{
    lcd_command( LCD_CLEAR_DISPLAY );
    _delay_ms( LCD_CLEAR_DISPLAY_MS );
}
 
////////////////////////////////////////////////////////////////////////////////
// Send: Cursor Home
void lcd_home( void )
{
    lcd_command( LCD_CURSOR_HOME );
    _delay_ms( LCD_CURSOR_HOME_MS );
}
 
////////////////////////////////////////////////////////////////////////////////
// Set cursor to X, Y 
 
void lcd_setcursor( uint8_t x, uint8_t y )
{
    uint8_t data;
 
    switch (y)
    {
        case 1:    // 1. Row
            data = LCD_SET_DDADR + LCD_DDADR_LINE1 + x;
            break;
 
        case 2:    // 2. Row
            data = LCD_SET_DDADR + LCD_DDADR_LINE2 + x;
            break;
 
        case 3:    // 3. Row
            data = LCD_SET_DDADR + LCD_DDADR_LINE3 + x;
            break;
 
        case 4:    // 4. Row
            data = LCD_SET_DDADR + LCD_DDADR_LINE4 + x;
            break;
 
        default:
            return;                                   
    }
 
    lcd_command( data );
}
 
////////////////////////////////////////////////////////////////////////////////
// send a String to the LCD
 
void lcd_string( const char *data )
{
    while( *data != '\0' )
        lcd_data( *data++ );
}
 
////////////////////////////////////////////////////////////////////////////////
// Send a Char to the LCD
 
void lcd_generatechar( uint8_t code, const uint8_t *data )
{
	uint8_t i=0;
    // set Startposition
    lcd_command( LCD_SET_CGADR | (code<<3) );
 
    // send bit pattern
    for ( i=0; i<8; i++ )
    {
        lcd_data( data[i] );
    }
}
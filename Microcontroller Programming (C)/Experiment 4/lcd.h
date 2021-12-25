// Control of a HD44780 LCD in 4-Bit-Interfacemode

 
#ifndef LCD_ROUTINES_H
#define LCD_ROUTINES_H
 
////////////////////////////////////////////////////////////////////////////////
// Define the MCUs frequency here
 
#ifndef F_CPU
#define F_CPU 8000000UL
#endif
 
////////////////////////////////////////////////////////////////////////////////
// Pinout of the LCD
 
//  LCD DB4-DB7 <-->  PORTD Bit PD0-PD3
#define LCD_PORT      PORTD
#define LCD_DDR       DDRD
#define LCD_DB        PD4
 
//  LCD RS      <-->  PORTD Bit PD4     (RS: 1=Data, 0=Command)
#define LCD_RS        PD2
 
//  LCD EN      <-->  PORTD Bit PD5     (EN: 1-Impuls for Data)
#define LCD_EN        PD3
 
////////////////////////////////////////////////////////////////////////////////
// LCD Timings (MS=Milliseconds, US=Microseconds)
 
#define LCD_BOOTUP_MS           15
#define LCD_ENABLE_US           20
#define LCD_WRITEDATA_US        46
#define LCD_COMMAND_US          42
 
#define LCD_SOFT_RESET_MS1      5
#define LCD_SOFT_RESET_MS2      1
#define LCD_SOFT_RESET_MS3      1
#define LCD_SET_4BITMODE_MS     5
 
#define LCD_CLEAR_DISPLAY_MS    2
#define LCD_CURSOR_HOME_MS      2
 
////////////////////////////////////////////////////////////////////////////////
// Row definitions
 
#define LCD_DDADR_LINE1         0x00
#define LCD_DDADR_LINE2         0x40
#define LCD_DDADR_LINE3         0x10
#define LCD_DDADR_LINE4         0x50
 
////////////////////////////////////////////////////////////////////////////////
// Initialise: 
void lcd_init( void );
 
////////////////////////////////////////////////////////////////////////////////
// LCD clear
void lcd_clear( void );
 
////////////////////////////////////////////////////////////////////////////////
// Cursor in the first row, first column
void lcd_home( void );
 
////////////////////////////////////////////////////////////////////////////////
// Cursor to a desired position
void lcd_setcursor( uint8_t spalte, uint8_t zeile );
 
////////////////////////////////////////////////////////////////////////////////
// Output a single char
void lcd_data( uint8_t data );
 
////////////////////////////////////////////////////////////////////////////////
// Output a string
void lcd_string( const char *data );
 
////////////////////////////////////////////////////////////////////////////////
// Define customised characters
void lcd_generatechar( uint8_t code, const uint8_t *data );
 
////////////////////////////////////////////////////////////////////////////////
// Output a command to the LCD
void lcd_command( uint8_t data );
 
 
////////////////////////////////////////////////////////////////////////////////
// LCD Commands
 
// Clear Display -------------- 0b00000001
#define LCD_CLEAR_DISPLAY       0x01
 
// Cursor Home ---------------- 0b0000001x
#define LCD_CURSOR_HOME         0x02
 
// Set Entry Mode ------------- 0b000001xx
#define LCD_SET_ENTRY           0x04
 
#define LCD_ENTRY_DECREASE      0x00
#define LCD_ENTRY_INCREASE      0x02
#define LCD_ENTRY_NOSHIFT       0x00
#define LCD_ENTRY_SHIFT         0x01
 
// Set Display ---------------- 0b00001xxx
#define LCD_SET_DISPLAY         0x08
 
#define LCD_DISPLAY_OFF         0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_CURSOR_OFF          0x00
#define LCD_CURSOR_ON           0x02
#define LCD_BLINKING_OFF        0x00
#define LCD_BLINKING_ON         0x01
 
// Set Shift ------------------ 0b0001xxxx
#define LCD_SET_SHIFT           0x10
 
#define LCD_CURSOR_MOVE         0x00
#define LCD_DISPLAY_SHIFT       0x08
#define LCD_SHIFT_LEFT          0x00
#define LCD_SHIFT_RIGHT         0x04
 
// Set Function --------------- 0b001xxxxx
#define LCD_SET_FUNCTION        0x20
 
#define LCD_FUNCTION_4BIT       0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_2LINE      0x08
#define LCD_FUNCTION_5X7        0x00
#define LCD_FUNCTION_5X10       0x04
 
#define LCD_SOFT_RESET          0x30
 
// Set CG RAM Address --------- 0b01xxxxxx  (Character Generator RAM)
#define LCD_SET_CGADR           0x40
 
#define LCD_GC_CHAR0            0
#define LCD_GC_CHAR1            1
#define LCD_GC_CHAR2            2
#define LCD_GC_CHAR3            3
#define LCD_GC_CHAR4            4
#define LCD_GC_CHAR5            5
#define LCD_GC_CHAR6            6
#define LCD_GC_CHAR7            7
 
// Set DD RAM Address --------- 0b1xxxxxxx  (Display Data RAM)
#define LCD_SET_DDADR           0x80
 
#endif 

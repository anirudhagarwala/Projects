################################################################################
# Makefile for MyAVR Programm                                                  #
# Lab five                                                                    #
################################################################################


# Options ######################################################################
PORT=COM5
PROGRAMMER=avr911
TARGET_CPU=atmega88pa
TARGET_PROCESSOR=m88p
CFLAGS=-Wall -Os -c -mmcu=$(TARGET_CPU)
LDFLAGS=-mmcu=$(TARGET_CPU)


# Program ######################################################################
all: main.hex
	echo main build complete

program: main.hex
	avrdude -p $(TARGET_PROCESSOR) -c $(PROGRAMMER) -P $(PORT) -U flash:w:main.hex:i

# Open GTK Terminal ############################################################
terminal:
	gtkterm -s 9600 -p $(PORT)


# Hex File #####################################################################
main.hex: main.elf
	avr-objcopy -O ihex main.elf main.hex

main.elf: main.o init.o lcd.o i2c_master.o
	avr-gcc $(LDFLAGS) main.o init.o lcd.o i2c_master.o -o main.elf



# Object Files #################################################################
init.o: init.c
	avr-gcc $(CFLAGS) init.c -o init.o

lcd.o: lcd.c
	avr-gcc $(CFLAGS) lcd.c -o lcd.o

i2c_master.o: i2c_master.c
	avr-gcc $(CFLAGS) i2c_master.c -o i2c_master.o

main.o: main.c
	avr-gcc $(CFLAGS) main.c -o main.o



# Clean ########################################################################
clean:
	rm -f *.o *.elf *.hex *~

CC = $(shell which avr-gcc)
CFLAGS = -mmcu=atmega2560 -std=c99
ASFLAGS = $(CFLAGS)
OBJCOPY= $(shell which avr-objcopy)
AVRDUDE = $(shell which avrdude)

SRCS = $(wildcard *.c)

.DEFAULT: program

program: assign2
	$(AVRDUDE) -c STK600 -p m2560 -U flash:w:$^

%: %.o

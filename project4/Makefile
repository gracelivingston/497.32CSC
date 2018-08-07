CC = $(shell which avr-gcc)
CFLAGS = -mmcu=atmega2560 -std=c11
ASFLAGS = $(CFLAGS)
OBJCOPY= $(shell which avr-objcopy)
AVRDUDE = $(shell which avrdude)

SRCS = $(wildcard *.S)
PRGS = $(SRCS:%.S=%)

.DEFAULT: program

program: project4
	$(AVRDUDE) -c STK600 -p m2560 -U flash:w:$^

%: %.o

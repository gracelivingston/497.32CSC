CC = $(shell which avr-gcc)
CFLAGS = -mmcu=atmega2560 -std=c11 -DF_CPU=8000000
OBJCOPY= $(shell which avr-objcopy)
AVRDUDE = $(shell which avrdude)

SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

.DEFAULT: program

program: serial-echo
	$(AVRDUDE) -c STK600 -p m2560 -U flash:w:$^

serial-echo: $(OBJS)

clean:
	rm -f $(OBJS) serial-echo

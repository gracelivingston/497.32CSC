// Special function registers

#ifndef _DRV_REG_H_
#define _DRV_REG_H_

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define _SFR(mem_addr) (*((volatile uint8_t *)(mem_addr)))

#define BIT(n) (1 << (n))

// Registers related to Port A
#define PINA _SFR(0x20)
#define DDRA _SFR(0x21)
#define PORTA _SFR(0x22)

// Registers related to Port B
#define PINB _SFR(0x23)
#define DDRB _SFR(0x24)
#define PORTB _SFR(0x25)

// Registers related to Timer/Counter 0
#define TCCR0A _SFR(0x44)
#define TCCR0B _SFR(0x45)

// Waveform Generation Mode for Timer/Counter 0
#define WGM00 BIT(0)
#define WGM01 BIT(1)
#define WGM02 BIT(3)

// Comparison A & B for Timer/Counter 0
#define COM0A0 BIT(6)
#define COM0A1 BIT(7)
#define COM0B0 BIT(4)
#define COM0B1 BIT(5)

// Clock Select for Timer/Counter 0
#define CS00 BIT(0)
#define CS01 BIT(1)
#define CS02 BIT(2)

#define CS_NONE 0
#define CS_IO (CS00)
#define CS_PSC_8 (CS01)
#define CS_PSC_64 (CS01 | CS00)
#define CS_PSC_256 (CS02)
#define CS_PSC_1024 (CS02 | CS00)

// Counter for Timer/Counter 0
#define TCNT0 _SFR(0x46)

// Counter Interrupt Flag Register for Timer/Counter 0
#define TIFR0 _SFR(0x35)

// Counter Overflow
#define TOV0 BIT(0)
#define OCF0A BIT(1)
#define OCF0B BIT(2)

// Output Compare Registers for Timer/Counter 0
#define OCR0A _SFR(0x47)
#define OCR0B _SFR(0x48)

#endif /* _DRV_REG_H_ */

// Special function registers

#ifndef _DRV_REG_H_
#define _DRV_REG_H_

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;

#define _SFR(mem_addr) (*(volatile uint8_t *)(mem_addr))

// Registers related to Port A
#define PINA _SFR(0x20)
#define DDRA _SFR(0x21)
#define PORTA _SFR(0x22)
#define PINB _SFR(0x23)
#define DDRB _SFR(0x24)
#define PORTB _SFR(0x25)

#endif /* _DRV_REG_H_ */

#include <avr/io.h>
#include <util/delay.h>

int bit_set(int byte, int bit)
{
    return (byte | (1 << (bit - 1)));
}

int bit_clr(int byte, int bit)
{
    return (byte & (~(1 << (bit - 1))));
}

int bit_tgl(int byte, int bit)
{
    return (byte ^ (1 << (bit - 1)));
}

int main(void)
{
    DDRB |= 0b00000011;

    for(unsigned i = 0; i <= 100; i++)
    {
        i % 4 == 0? PORTB &= ~(0b10) : 0;
        i % 6 == 0? PORTB |= 0b10 : 0;
        _delay_ms(3);
    }

    TCCR0A = bit_set(TCCR0A, COM0A0);
    TCCR0A = bit_clr(TCCR0A, COM0A1);

    TCCR0A = bit_clr(TCCR0A, WGM00);
    TCCR0A = bit_set(TCCR0A, WGM01);

    TCCR0B = bit_set(TCCR0B, CS00);

    OCR0A = 255;

    while(1);

}
#include <avr/io.h>
#include <util/delay.h>

int bit_set(int byte, int bit)
{
    return (byte | (1 << bit));
}

int bit_rst(int byte, int bit)
{
    return (byte & (~(1 << bit)));
}

int bit_tgl(int byte, int bit)
{
    return (byte ^ (1 << bit));
}

int bit_chk(int byte, int bit)
{
    return (byte >> bit) & 1;
}

int main(void)
{
    //OSCCAL = 0b10010101; // calibration value

    //CLKPR = 0b10000000;
    //CLKPR = 0b00000000;

    PLLCSR = bit_rst(PLLCSR, LSM); // PLL high-speed mode
    PLLCSR = bit_set(PLLCSR, PLLE); // Enable PLL

    // Wait for PLL to stabilize
    _delay_us(100); 
    while(bit_chk(PLLCSR, PLOCK) == 0);

    PLLCSR = bit_set(PLLCSR, PCKE); // Enable PLL as clock source for T1

    DDRB |= 0b00000011;

    for(unsigned i = 0; i <= 100; i++)
    {
        i % 4 == 0? PORTB &= ~(0b10) : 0;
        i % 6 == 0? PORTB |= 0b10 : 0;
        _delay_ms(10);
    }

    TCCR1 = 0;

    // T1 mode, CTC
    TCCR1 = bit_set(TCCR0A, CTC1);
    OCR1C = 0; // Value to compare

    // Toggle PB1
    TCCR1 = bit_set(TCCR1, COM1A0);
    TCCR1 = bit_rst(TCCR1, COM1A1);

    // Enable T1 clock, no prescaler
    TCCR1 = bit_set(TCCR1, CS10);

    while(1);

}

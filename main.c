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
    OSCCAL = 0b10101101; // calibration value

    /* Timer 1 */

    DDRB = bit_set(DDRB, PB4);

    //PLLCSR = bit_rst(PLLCSR, LSM); // PLL high-speed mode
    //PLLCSR = bit_set(PLLCSR, PLLE); // Enable PLL

    // Wait for PLL to stabilize
    //_delay_us(100); 
    //while(bit_chk(PLLCSR, PLOCK) == 0); // PCKE can be safely set only when lock bit is 1

    PLLCSR = bit_set(PLLCSR, PCKE); // Enable PLL as clock source for T1

    // T1 mode, CTC
    TCCR1 = bit_set(TCCR1, CTC1);
    OCR1C = 2; // Value to compare

    // Toggle mode, PB4
    GTCCR = bit_set(GTCCR, COM1B0);
    GTCCR = bit_rst(GTCCR, COM1B1);

    // PWM mode, PB1
    //TCCR1 = bit_set(TCCR1, PWM1A);
    //OCR1A = 1;

    // Enable T1 clock, no prescaler
    TCCR1 = bit_rst(TCCR1, CS13);
    TCCR1 = bit_rst(TCCR1, CS12);
    TCCR1 = bit_rst(TCCR1, CS11);
    TCCR1 = bit_set(TCCR1, CS10);

    

    /* Analog comparator */
    
    // ENABLE AIN1 multiplexer
    ADCSRB = bit_set(ADCSRB, ACME);

    // Select ADC1, PB2
    ADMUX = bit_set(ADMUX, MUX0);

    // Interrupt on rising
    ACSR = bit_set(ACSR, ACIS1);
    ACSR = bit_set(ACSR, ACIS0);

    // Enable interrupt
    ACSR = bit_set(ACSR, ACIE);

    // Enable AC
    ACSR = bit_rst(ACSR, ACD);

    

    /* Timer 0 */

    DDRB = bit_set(DDRB, PB1);

    // CTC, OC0B, PB1
    TCCR0A = bit_rst(TCCR0A, COM0B1);
    TCCR0A = bit_set(TCCR0A, COM0B0);

    // Compare mode
    TCCR0B = bit_rst(TCCR0B, WGM02);
    TCCR0A = bit_set(TCCR0A, WGM01);
    TCCR0A = bit_rst(TCCR0A, WGM00);

    // T0 prescaler /1
    TCCR0B = bit_rst(TCCR0B, CS02);
    TCCR0B = bit_rst(TCCR0B, CS01);
    TCCR0B = bit_set(TCCR0B, CS00);

    OCR0A = 11;

    while(1)
    {
        ;
    }

}

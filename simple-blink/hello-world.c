#include <avr/io.h>
#include <util/delay.h>

// Shift the passed bit on the port data direction register to set it as output
void setup_bit_as_output(int bit)
{
    if (bit == 5)
    {
        DDRB |= (1 << DDB5);
    }
    else if (bit == 4)
    {
        DDRB |= (1 << DDB4);
    }
    else if (bit == 2)
    {
        DDRB |= (1 << DDB4);
    }
}

// Take the current bit values of PORTB, then get the complement of shifting the passed bit.
// Then, use the bitwise AND to assign a new value to PORTB
// Bitwise AND combined with the complement value will leave all current 1 values unchanged but set all others to 0
void switch_power_off(int bit)
{
    if (bit == 5)
    {
        PORTB &= ~(1 << PORTB5);
    }
    else if (bit == 4)
    {
        PORTB &= ~(1 << PORTB4);
    }
    else if (bit == 2)
    {
        PORTB &= ~(1 << PORTB2);
    }
}

// Shift the passed bit to power the port
void switch_power_on(int bit)
{
    if (bit == 5)
    {
        PORTB |= (1 << PORTB5);
    }
    else if (bit == 4)
    {
        PORTB |= (1 << PORTB4);
    }
    else if (bit == 2)
    {
        PORTB |= (1 << PORTB2);
    }
}

int main(void)
{
    setup_bit_as_output(5);
    setup_bit_as_output(4);
    setup_bit_as_output(2);

    for(;;)
    {
        switch_power_on(5);
        switch_power_off(4);
        switch_power_on(2);
        _delay_ms(500);
        switch_power_off(5);
        switch_power_on(4);
        switch_power_off(2);
        _delay_ms(500);
    }
}
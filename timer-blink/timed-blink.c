#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

bool light_on;

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

    light_on = false;
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

    light_on = true;
}

void toggle_led(int bit)
{
    if (light_on)
    {
        switch_power_off(bit);
    }
    else
    {
        switch_power_on(bit);
    }
    
}

int main(void)
{
    setup_bit_as_output(5);

    TCCR1B |= (1 << CS10); // How do we know to use this clock source??

    for(;;)
    {

        if (TCNT1 >= 49999)
        {
            toggle_led(5);
            TCNT1 = 0;
        }
    }
}
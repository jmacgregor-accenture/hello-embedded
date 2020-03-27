#include <avr/io.h>
#include <util/delay.h>

// Shift 5th bit on the port data direction register to set it as output
void setup_onboard_led_as_output()
{
    DDRB |= (1 << DDB5);
}

// Shift 5th bit to power the port
void onboard_led_on()
{
    PORTB |= (1 << PORTB5);
}

// Take the current bit values of PORTB, then get the complement of shifting the 5th bit.
// Then, use the bitwise AND to assign a new value to PORTB
// Bitwise AND combined with the complement value will leave all current 1 values unchanged but set all others to 0 
void onboard_led_off()
{
    PORTB &= ~(1 << PORTB5);
}

void setup_offboard_led()
{
    DDRB |= (1 << DDB4);
}

void offboard_led_on()
{
    PORTB |= (1 << PORTB4);
}

void offboard_led_off()
{
    PORTB &= ~(1 << PORTB4);
}

int main(void)
{
    setup_onboard_led_as_output();
    setup_offboard_led();

    for(;;)
    {
        offboard_led_off();
        onboard_led_on();
        _delay_ms(500);
        offboard_led_on();
        onboard_led_off();
        _delay_ms(500);
    }
}
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

// I actually have no idea what the & is doing, exactly
// right right-hand side is shifting the 5th bit in the opposite 
// direction as before
// but instead of piping that to make an assignment, we make the 
// port = 0 because current value of portb and the ~'d result of the 
// 5th bit are not equal
void onboard_led_off()
{
    PORTB &= ~(1 << PORTB5);
}

int main(void)
{
    setup_onboard_led_as_output();

    for(;;)
    {
        onboard_led_on();
        _delay_ms(250);
        onboard_led_off();
        _delay_ms(750);
    }
}
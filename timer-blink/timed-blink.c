#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

bool light_on;

// Shift the passed bit on the port data direction register to set it as output
void setup_onboard_led_as_output()
{
    DDRB |= (1 << DDB5);
}

void toggle_led()
{
    PORTB ^= (1 << PORTB5);
}

int main(void)
{
    setup_onboard_led_as_output();

    TCCR1B |= (1 << CS10);

    for(;;)
    {

        if (TCNT1 >= 49999)
        {
            toggle_led();
            TCNT1 = 0;
        }
    }
}
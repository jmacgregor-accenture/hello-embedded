#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

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

ISR(TIMER1_OVF_vect)        // interrupt service routine
{
    toggle_led();
}

void timer_setup()
{
    TCCR1A = 0x00;
    TCCR1B |= (1 << CS10);
    TIMSK1 = (1 << TOIE1);
}

int main(void)
{
    setup_onboard_led_as_output();

    cli();
    timer_setup();
    sei(); // enable global interrupt
    
    // setting any kind of sleep mode in the loop prevents the light
    //set_sleep_mode(SLEEP_MODE_STANDBY);

    for(;;)
    {
        //sleep_mode();
        //sei();
    }
}
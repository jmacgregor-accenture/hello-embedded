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

ISR(TIMER1_OVF_vect) // interrupt service routine
{
    toggle_led();
}

void timer_setup()
{
    cli();
    TCCR1A = 0x00; // Clear the A side register
    TCCR1B |= (1 << CS12); // use setting 12 to achieve ~1 sec overflow
    TIMSK1 = (1 << TOIE1); // enable overflow intterup on timer1 interrupt mask
    sei();
}

int main(void)
{
    setup_onboard_led_as_output();
    timer_setup();
    set_sleep_mode(SLEEP_MODE_IDLE); // lowest energy mode that keeps timer1 running

    for(;;)
    {
        sleep_mode();
    }
}
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>

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

void timer_setup(bool fastBlink)
{
    cli(); // clear interrupts
    TCCR1A = 0x00; // Clear the A side register

    if (fastBlink)
    {
        TCCR1B |= ((1 << CS10) | (1 << CS11)); // 1/64 prescaler to make overflow ~.25 second
    }
    else
    {
        TCCR1B |= (1 << CS12); // 1/256 prescaler to make overflow ~1 second
    }
    
    TIMSK1 = (1 << TOIE1); // enable overflow interrupt on timer1 interrupt mask
    sei();
}

int main(void)
{
    setup_onboard_led_as_output();
    timer_setup(false);
    set_sleep_mode(SLEEP_MODE_IDLE); // lowest energy mode that keeps timer1 running

    for(;;)
    {
        sleep_mode();
    }
}
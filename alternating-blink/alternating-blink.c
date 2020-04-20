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

ISR(TIMER1_COMPA_vect) // interrupt service routine
{
    toggle_led();
}

void timer_setup()
{
    cli(); // clear interrupts
    TCCR1A = 0x00; // Clear the A side register

    TCCR1B |= (1 << WGM12); // configure CTC mode
    OCR1A = 15624; // set ticks per second
    TCCR1B |= ((1 << CS12) | (1 << CS10)); // 1/1024 prescaler to make overflow ~4 seconds
    
    TIMSK1 = (1 << OCIE1A); // enable CTC interrupt on timer1 interrupt mask
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
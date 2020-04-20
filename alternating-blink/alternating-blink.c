#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <stdbool.h>

const int LED_ON_SECOND = 1;
const int LED_OFF_SECOND = 3;
const unsigned int TICKS_PER_SECOND = 15624; // ticks per second at 16mhz & 1024 prescaler
unsigned int ONE_SECOND_TICKS = LED_ON_SECOND * TICKS_PER_SECOND; 
unsigned int THREE_SECOND_TICKS = LED_OFF_SECOND * TICKS_PER_SECOND;

// Shift the passed bit on the port data direction register to set it as output
void setup_onboard_led_as_output()
{
    DDRB |= (1 << DDB5);
}

void toggle_led()
{
    PORTB ^= (1 << PORTB5);
}

ISR(TIMER1_COMPA_vect) // configured to trigger 1st
{
    toggle_led();
}

ISR(TIMER1_COMPB_vect) // configured to trigger 2nd
{
    toggle_led();
    TCNT1 = 0; // allow timer to start over again
}

void timer_setup()
{
    cli(); // clear interrupts
    TCCR1A = 0x00; // Clear the A side register

    TCCR1B |= ((1<< WGM13) | (1 << WGM12)); // configure CTC mode on both channels
    OCR1A = ONE_SECOND_TICKS;
    OCR1B = THREE_SECOND_TICKS;
    TCCR1B |= ((1 << CS12) | (1 << CS10)); // 1/1024 prescaler to make overflow ~4 seconds
    
    TIMSK1 |= ((1 << OCIE1A) | (1 << OCIE1B)); // enable CTC interrupt on timer1 interrupt mask
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
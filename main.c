
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
//#include "pid.h"

// ----------------------------------------------------------------------------
//              ------
//ADC0/RES    -| -    |-  VCC
//ADC3/PB3    -|      |-  PB2/SCK/ADC1
//ADC2/PB4    -|      |-  PB1/MISO/OC0B
//     GND    -|      |-  PB0/MOSI/OC0A
//              ------
// ----------------------------------------------------------------------------

#define MAX_PWM 0x10

ISR(TIM0_OVF_vect)
{

  PORTB &= ~(1 << PB0); // High Voltage
}

static inline void initTimer0(void)
{
  // Timer 0 Configuration
  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00)  // Prescaler = 1
           | (1 << WGM02); //Fast PWM
//  TCCR0A |= ((1 << COM0B1) | (0 << COM0B0) // Clear PORT OC0B on OCR0B match
//            | (1 << COM0A1) | (0 << COM0A0) // Clear PORT OC0A on OCR0A match
//            | (1 << WGM00) | (1 << WGM01));

  // Set to 'Fast PWM' mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00);
  TIMSK0 |= (1 << TOIE0);

// Clear OC0B output on compare match, upwards counting.
  TCCR0A |= (1 << COM0B1);
  OCR0B = MAX_PWM/4+MAX_PWM/8;  // Filament setting
  OCR0A = MAX_PWM;
}

void adc_setup (void)
{
    // Set the ADC input to PB2/ADC1
    ADMUX |= (1 << MUX0);
    ADMUX |= (1 << ADLAR);

    // Set the prescaler to clock/128 & enable ADC
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0) | (1 << ADEN);
}


int adc_read (void)
{
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for it to finish - blocking
    while (ADCSRA & (1 << ADSC));

    return ADCH;
}

int main(void)
{

  // ---- Initialization ----

  DDRB |= (1 << PB0) | (1 << PB1);

  initTimer0();
  adc_setup();


  sei();

  // ---- Main Loop ----

  while (1)
  {
      PORTB |= (1 << PB0);  // High voltage.
      
      // OCR0B = adc_read(); //MAX_PWM/4+MAX_PWM/8;  // Filament setting
  }

  return 0;
}

// ============================================================================

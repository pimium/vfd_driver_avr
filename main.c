
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

#define MAX_PWM 0x28

static inline void initTimer0(void)
{
  // Timer 0 Configuration
  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00)  // Prescaler = 1
           | (1 << WGM02); //Fast PWM

  TCCR0A |= (0 << COM0A1) | (0 << COM0A0); // Clear PORT OC0A on Top
  TCCR0A |= (1 << COM0B1) | (0 << COM0B0);

  // Set to 'Fast PWM' mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00);

  OCR0B = MAX_PWM/4+MAX_PWM/8;  // Filament setting
  OCR0A = MAX_PWM;
}

int main(void)
{

  // ---- Initialization ----

  DDRB |= (1 << PB0) | (1 << PB1);

  initTimer0();

  sei();

  // ---- Main Loop ----

  while (1)
  {
      PORTB &= ~(1 << PB0);  // High voltage
      PORTB &= ~(1 << PB0);  // High voltage
//      PORTB &= ~(1 << PB0);  // High voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
      PORTB |= (1 << PB0); // High Voltage
  }

  return 0;
}

// ============================================================================

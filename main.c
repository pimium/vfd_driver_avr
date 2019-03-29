
#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
//#include "pid.h"

#define RCLK PB2
#define DATA PB0
#define SRCLK PB1
#define SRCLR PB4
#define GRAD PB3

// ----------------------------------------------------------------------------
//              ------
//ADC0/RES    -| -    |-  VCC
//ADC3/PB3    -|      |-  PB2/SCK/ADC1
//ADC2/PB4    -|      |-  PB1/MISO/OC0B
//     GND    -|      |-  PB0/MOSI/OC0A
//              ------
// ----------------------------------------------------------------------------

#define MAX_PWM 0x20

static inline void initTimer0(void)
{
  // Timer 0 Configuration
  TCCR0B |= (0 << CS02) | (0 << CS01) | (1 << CS00)  // Prescaler = 1
           | (1 << WGM02); //Fast PWM

  TCCR0A |= (0 << COM0A1) | (0 << COM0A0); // Clear PORT OC0A on Top
  TCCR0A |= (1 << COM0B1) | (0 << COM0B0);

  // Set to 'Fast PWM' mode
  TCCR0A |= (1 << WGM01) | (1 << WGM00);

  OCR0B = MAX_PWM >> 1; //+MAX_PWM/8;  // Filament setting
  OCR0A = MAX_PWM;
}

int main(void)
{

  // ---- Initialization ----

  DDRB |= (1 << RCLK) | (1 << DATA) | (1 << SRCLK) | (1 << SRCLR) | (1 << GRAD);

//  initTimer0();
//  sei();

  // ---- Main Loop ----
    PORTB &= ~(1 << SRCLR);
    PORTB &= ~(1 << SRCLK);
    PORTB &= ~(1 << RCLK);
    PORTB |= (1 << SRCLR);
  while (1)
  {
      for (int i = 0; i < 8; ++i)
      {
          PORTB |= (1 << DATA);
          PORTB |= (1 << SRCLK);
          PORTB |= (1 << SRCLK);
          PORTB &= ~(1 << SRCLK);

          PORTB &= ~(1 << RCLK);
      }

      for (int j = 0; j < 8; ++j)
          PORTB |= (1 << RCLK);m

//      PORTB ^= (1 << DATA);
  }

  return 0;
}

// ============================================================================

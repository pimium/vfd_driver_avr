
#include <avr/interrupt.h>

#include "vfd.h"
#include <avr/io.h>
#include <stdint.h>

#define RCLK PB2
#define DATA PB0
#define SRCLK PB1
#define SRCLR PB4
#define GRAD PB3
//
////
///----------------------------------------------------------------------------
////              ------
////ADC0/RES    -| -    |-  VCC
////ADC3/PB3    -|      |-  PB2/SCK/ADC1
////ADC2/PB4    -|      |-  PB1/MISO/OC0B
////     GND    -|      |-  PB0/MOSI/OC0A
////              ------
////
///----------------------------------------------------------------------------

#define MAX_PWM 0x20

int main(void)
{

    // ---- Initialization ----
    vfd_init();
    //  sei();

    // ---- Main Loop ----

    while (1)
    {

        //    vfd_write_word(0, 10);
        vfd_write_word(1, 8);
        //    vfd_write_word(2, 10);
        vfd_write_word(3, 9);
        //    vfd_write_word(4, 10);
        //    vfd_write_word(5, 10);
        //    vfd_write_word(6, 10);
        vfd_write_special_character(0);
        //      vfd_write_special_character(1);
        //      vfd_write_special_character(2);
        //      vfd_write_special_character(3);
        //      vfd_write_special_character(4);
        //      vfd_write_special_character(5);
        //      vfd_write_special_character(11);
    }

    return 0;
}

// ============================================================================

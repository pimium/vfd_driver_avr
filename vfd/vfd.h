//
// Created by pimi on 29.03.19.
//

#include <avr/io.h>

#ifndef SMPS_VFD_H
#define SMPS_VFD_H

#define RCLK PB2
#define DATA PB0
#define SRCLK PB1
#define SRCLR PB4
#define GRAD PB3
#ifndef VFD_PORT
#define VFD_PORT PORTB
#endif
#ifndef VFD_DDR
#define VFD_DDR DDRB
#endif

// ----------------------------------------------------------------------------
//              ------
// ADC0/RES    -| -    |-  VCC
// ADC3/PB3    -|      |-  PB2/SCK/ADC1
// ADC2/PB4    -|      |-  PB1/MISO/OC0B
//      GND    -|      |-  PB0/MOSI/OC0A
//              ------
// ----------------------------------------------------------------------------
void vfd_init(void);
// void vfd_write_byte(uint8_t byte);
void vfd_write_special_character(uint8_t pos);
uint8_t vfd_write_word(uint8_t pos, uint8_t value);
void vfd_blank(void);
uint16_t vfd_convert_bcd(uint16_t binaryInput);
// void vfd_write_special_character(uint8_t posit, uint8_t filament, uint8_t
// symb);
#endif // SMPS_VFD_H

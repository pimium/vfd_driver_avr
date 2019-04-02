//
// Created by pimi on 29.03.19.
//

#include <stdint.h>
#include "vfd.h"
#include <avr/pgmspace.h>

#define MESSAGE_LENGTH 8

const uint8_t dec[][2] PROGMEM = {{0x80, 0x6D}, // 0
                                  {0x00, 0x28}, // 1
                                  {0x20, 0x65}, // 2
                                  {0x20, 0x6C}, // 3
                                  {0xA0, 0x28}, // 4
                                  {0xA0, 0x4C}, // 5
                                  {0xA0, 0x4D}, // 6
                                  {0x00, 0x68}, // 7
                                  {0xA0, 0x6D}, // 8
                                  {0xA0, 0x6C}, // 9
                                  {0,    0}}; // Nothing
const uint8_t position[][2] PROGMEM = {{0x02, 0x04}, // G7
                                       {0x02, 0x20}, // G6
                                       {0x01, 0x01}, // G5
                                       {0x01, 0x10}, // G4
                                       {0x01, 0x40}, // G3
                                       {0x00, 0x02}, // G2
                                       {0x00, 0x10}, // G1
};
const uint8_t symbole[][2] = {{0x21, 0x80}, //Glocke
                              {0x22, 0x40}, // Ofen
                              {0x22, 0x08}, // D
                              {0x10, 0x08}, // A am
                              {0x10, 0x04}, // P pm
                              {0x10, 0x02}, // Auto
                              {0x22, 0x10}, // :
                              {0x23, 0x08}, // Stop
                              {0x24, 0x02}, // Kolben
                              {0x25, 0x01}, // Kasten
                              {0x26, 0x08}, // Start
                              {0x06, 0x80}, // Celcius
};

void vfd_init(void)
{
    DDRB |= (1 << RCLK) | (1 << DATA) | (1 << SRCLK) | (1 << SRCLR) | (1 << GRAD);
    PORTB &= ~(1 << SRCLR);
    PORTB &= ~(1 << SRCLK);
    PORTB &= ~(1 << RCLK);

    PORTB |= (1 << SRCLR);

    PORTB &= (1 << GRAD);
}

void vfd_write_byte(uint8_t byte)
{

    int i = MESSAGE_LENGTH;
    do
    {
        if (byte & 0x01)
            PORTB |= (1 << DATA);
        else
            PORTB &= ~(1 << DATA);

        PORTB &= ~(1 << SRCLK);
        byte = byte >> 1;
        i--;

        PORTB |= (1 << SRCLK);
    } while (i > 0);
}

void vfd_write_word(uint8_t pos, uint8_t value)
{

    uint8_t pos_value = pgm_read_byte(&position[pos][1]);
    uint8_t posi = pgm_read_byte(&position[pos][0]);

    uint32_t deci = pgm_read_byte(&dec[value][1]);

    PORTB |= (1 << SRCLR);
    uint8_t byte_value = deci;
    if (posi == 0)
        byte_value = pos_value | byte_value;
    vfd_write_byte(byte_value);
    PORTB &= ~(1 << RCLK);

    deci = pgm_read_byte(&dec[value][0]);
    byte_value = deci;
    if (posi == 1)
        byte_value = pos_value | byte_value;
    vfd_write_byte(byte_value);

    deci = 0;
    byte_value = deci;
    if (posi == 2)
        byte_value = pos_value | byte_value;
    vfd_write_byte(byte_value);
    PORTB |= (1 << RCLK);
}

void vfd_write_special_character(uint8_t symb)
{
    uint8_t register_value[3] = {0, 0, 0};

    uint8_t filament_byte = symbole[symb][0];
    uint8_t symb_value = symbole[symb][1];

    PORTB |= (1 << SRCLR);
    uint8_t filament_nr = (filament_byte >> 4);
    uint8_t byte_position = filament_byte & 0xf;

    uint8_t posit = pgm_read_byte(&position[byte_position][0]);

    register_value[filament_nr] = symb_value;
    register_value[posit] = register_value[posit] | pgm_read_byte(&position[byte_position][1]);

    vfd_write_byte(register_value[0]);
    PORTB &= ~(1 << RCLK);
    vfd_write_byte(register_value[1]);
    vfd_write_byte(register_value[2]);
    PORTB |= (1 << RCLK);
}

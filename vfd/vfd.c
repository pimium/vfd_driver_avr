//
// Created by pimi on 29.03.19.
//

#include "vfd.h"
#include <avr/pgmspace.h>
#include <stdint.h>

#define MESSAGE_LENGTH 8

static uint8_t register_value[3] = {0, 0, 0};

const uint8_t decimal_list[][2] = {
    {0x80, 0x6D}, // 0
    {0x00, 0x28}, // 1
    {0x20, 0x65}, // 2
    {0x20, 0x6C}, // 3
    {0xA0, 0x28}, // 4
    {0xA0, 0x4C}, // 5
    {0xA0, 0x4D}, // 6
    {0x00, 0x68}, // 7
    {0xA0, 0x6D}, // 8
    {0xA0, 0x6C}, // 9
    {0, 0}        // Blank
};

const uint8_t position_list[][2] = {
    {0x02, 0x04}, // G7
    {0x02, 0x20}, // G6
    {0x01, 0x01}, // G5
    {0x01, 0x10}, // G4
    {0x01, 0x40}, // G3
    {0x00, 0x02}, // G2
    {0x00, 0x10}  // G1
};

const uint8_t symbole_list[][2] = {
    {0x21, 0x80}, // Glocke
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

void set_register_value(uint8_t value1, uint8_t value2, uint8_t value3)
{
    register_value[0] = value1;
    register_value[1] = value2;
    register_value[2] = value3;
}

void get_register_value(uint8_t *reg)
{
    reg[0] = register_value[0];
    reg[1] = register_value[1];
    reg[2] = register_value[2];
}

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
    uint8_t position_value = position_list[pos][1];
    uint8_t position = position_list[pos][0];

    register_value[0] = ((decimal_list[value][1]));
    register_value[1] = ((decimal_list[value][0]));
    register_value[2] = 0;
    register_value[position] = register_value[position] | position_value;

    PORTB |= (1 << SRCLR);
    vfd_write_byte(register_value[0]);
    PORTB &= ~(1 << RCLK);
    vfd_write_byte(register_value[1]);
    vfd_write_byte(register_value[2]);
    PORTB |= (1 << RCLK);
}

//
void vfd_write_special_character(uint8_t symb)
{
    register_value[0] = 0;
    register_value[1] = 0;
    register_value[2] = 0;

    uint8_t filament_byte = symbole_list[symb][0];
    uint8_t symb_value = symbole_list[symb][1];

    PORTB |= (1 << SRCLR);
    uint8_t filament_nr = (filament_byte >> 4);
    uint8_t byte_position = filament_byte & 0xf;

    uint8_t posit = position_list[byte_position][0];

    register_value[filament_nr] = symb_value;
    register_value[posit] = register_value[posit] | position_list[byte_position][1];

    vfd_write_byte(register_value[0]);
    PORTB &= ~(1 << RCLK);
    vfd_write_byte(register_value[1]);
    vfd_write_byte(register_value[2]);
    PORTB |= (1 << RCLK);
}

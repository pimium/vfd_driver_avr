//
// Created by pimi on 07.04.19.
//

#ifndef SMPS_VFD_TEST_H
#define SMPS_VFD_TEST_H
void set_register_value(uint8_t value1, uint8_t value2, uint8_t value3);
void get_register_value(uint8_t *reg);
void get_value_position(uint8_t *reg);
void get_value_symbol(uint8_t reg[7][2]);

#endif // SMPS_VFD_TEST_H

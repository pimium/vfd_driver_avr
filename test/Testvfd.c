
#include "vfd.h"
#include "vfd_test.h"
#include <unity.h>

#define REG_INIT_0 0x80
#define REG_INIT_1 0x81
#define REG_INIT_2 0x82

/* sometimes you may want to get at local data in a module.
 * for example: If you plan to pass by reference, this could be useful
 * however, it should often be avoided */

void setUp(void)
{
    /* This is run before EACH TEST */
    // set_register_value(REG_INIT_0, REG_INIT_1, REG_INIT_2);
    vfd_blank();
}

void tearDown(void) {}

void test_InitFunction_dummy(void)
{
    uint8_t register_value[3];
    vfd_init();
    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[2]);
}

void test_vfd_write_word_for_position_0(void)
{
    uint8_t value_position_copy[7];
    uint8_t value = 45;
    TEST_ASSERT_EQUAL_HEX8(0, vfd_write_word(0, value));
    get_value_position(value_position_copy);
    TEST_ASSERT_EQUAL_HEX8(value, value_position_copy[0]);
}

void test_vfd_write_word_for_position_6(void)
{
    uint8_t value_position_copy[7];
    uint8_t value = 255;
    TEST_ASSERT_EQUAL_HEX8(0, vfd_write_word(6, value));
    get_value_position(value_position_copy);
    TEST_ASSERT_EQUAL_HEX8(value, value_position_copy[6]);
}

void test_vfd_write_word_for_position_7(void)
{
    uint8_t value_position_copy[7];
    TEST_ASSERT_EQUAL_HEX8(1, vfd_write_word(7, 0x10));
    get_value_position(value_position_copy);
}

void test_vfd_write_word_for_position_3(void)
{
    uint8_t value_position_copy[7];
    uint8_t value = 25;
    TEST_ASSERT_EQUAL_HEX8(0, vfd_write_word(3, value));
    get_value_position(value_position_copy);
    TEST_ASSERT_EQUAL_HEX8(value, value_position_copy[3]);
}

// 0 {0x21, 0x80}, // Glocke
void test_vfd_write_special_character_Glocke(void)
{
    uint8_t reg[7][2];

    vfd_write_special_character(0);
    get_value_symbol(reg);
    TEST_ASSERT_EQUAL_HEX8(0x02, reg[1][0]);
    TEST_ASSERT_EQUAL_HEX8(0x80, reg[1][1]);
}

// 2 {0x10, 0x02}, // Auto
void test_vfd_write_special_character_Auto(void)
{
    uint8_t reg[7][2];

    vfd_write_special_character(2);
    get_value_symbol(reg);
    TEST_ASSERT_EQUAL_HEX8(0x01, reg[0][0]);
    TEST_ASSERT_EQUAL_HEX8(0x02, reg[0][1]);
}

// 4 {0x24, 0x02}, // Kolben
void test_vfd_write_special_character_Kolben(void)
{
    uint8_t reg[7][2];

    vfd_write_special_character(4);
    get_value_symbol(reg);
    TEST_ASSERT_EQUAL_HEX8(0x02, reg[4][0]);
    TEST_ASSERT_EQUAL_HEX8(0x02, reg[4][1]);
}


void test_vfd_states_set_rclK_actual_register_0x3(void)
{
    uint8_t reg[7][2];

    vfd_states_set_rclK();
    vfd_write_special_character(4);
    get_value_symbol(reg);
    TEST_ASSERT_EQUAL_HEX8(0x02, reg[4][0]);
    TEST_ASSERT_EQUAL_HEX8(0x02, reg[4][1]);
}

/*
void test_vfd_write_word_for_decimal_0(void)
{
    uint8_t register_value[3];
    vfd_write_word(2, 0);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(0x6D, 0x6D & register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0x80, 0x80 & register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[2]);
}
*/
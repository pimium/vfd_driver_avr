
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
    set_register_value(REG_INIT_0, REG_INIT_1, REG_INIT_2);
}

void tearDown(void) {}

void test_InitFunction_dummy(void)
{
    uint8_t register_value[3];
    vfd_init();
    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_0, register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_1, register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_2, register_value[2]);
}

// 0 {0x21, 0x80}, // Glocke
void test_vfd_write_special_character_Glocke(void)
{
    uint8_t register_value[3];
    vfd_write_special_character(0);
    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_0, register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_1, register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x80 | 0x20, (0x80 | 0x20) & register_value[2]);
}

// 5 {0x10, 0x02}, // Auto
void test_vfd_write_special_character_Auto(void)
{
    uint8_t register_value[3];
    vfd_write_special_character(5);
    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_0, register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0x02, register_value[1]);
    TEST_ASSERT_EQUAL_HEX8((REG_INIT_2 | 0x04), (REG_INIT_2 | 0x04) & register_value[2]);
    
}

// 8 {0x24, 0x02}, // Kolben
void test_vfd_write_special_character_Kolben(void)
{
    uint8_t register_value[3];
    vfd_write_special_character(8);
    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(REG_INIT_0, register_value[0]);
    TEST_ASSERT_EQUAL_HEX8((REG_INIT_1 | 0x40), (REG_INIT_1 | 0x40) & register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x02, 0x02 | register_value[2]);
    
}

// write the decimal 0 to the display: {0x80, 0x6D}, // 0
void test_vfd_write_word_for_decimal_0(void)
{
    uint8_t register_value[3];
    vfd_write_word(2, 0);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(0x6D, 0x6D & register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0x80, 0x80 & register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[2]);
}

// write the decimal 3 to the display: {0x20, 0x6C}, // 3
void test_vfd_write_word_for_decimal_3(void)
{
    uint8_t register_value[3];
    vfd_write_word(0, 3);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(0x6C, 0x6C & register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0x20, 0x20 & register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x04, register_value[2]);
}

// write the decimal 9 to the display: {0xA0, 0x6C}, // 9
void test_vfd_write_word_for_decimal_9(void)
{
    uint8_t register_value[3];
    vfd_write_word(0, 9);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(0x6C, 0x6C & register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0xA0, 0xA0 & register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x04, register_value[2]);
}

void test_vfd_write_word_for_blanking(void)
{
    uint8_t register_value[3];
    vfd_write_word(0, 10);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[0]);
    TEST_ASSERT_EQUAL_HEX8(0x00, register_value[1]);
    TEST_ASSERT_EQUAL_HEX8(0x04, register_value[2]);
}

void test_vfd_write_word_for_position_0(void)
{
    uint8_t register_value[3];
    vfd_write_word(0, 0);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x4, 0x4 & register_value[2]);
}

void test_vfd_write_word_for_position_1(void)
{
    uint8_t register_value[3];
    vfd_write_word(1, 9);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x20, 0x20 & register_value[2]);
}

void test_vfd_write_word_for_position_2(void)
{
    uint8_t register_value[3];
    vfd_write_word(2, 8);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x01, 0x01 & register_value[1]);
}

void test_vfd_write_word_for_position_3(void)
{
    uint8_t register_value[3];
    vfd_write_word(3, 6);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x10, 0x10 & register_value[1]);
}

void test_vfd_write_word_for_position_4(void)
{
    uint8_t register_value[3];
    vfd_write_word(4, 5);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x40, 0x40 & register_value[1]);
}

void test_vfd_write_word_for_position_5(void)
{
    uint8_t register_value[3];
    vfd_write_word(5, 4);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x02, 0x02 & register_value[0]);
}

void test_vfd_write_word_for_position_6(void)
{
    uint8_t register_value[3];
    vfd_write_word(6, 3);

    get_register_value(register_value);
    TEST_ASSERT_EQUAL(0x10, 0x10 & register_value[0]);
}

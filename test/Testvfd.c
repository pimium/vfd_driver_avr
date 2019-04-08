
#include "vfd.h"
#include "vfd_test.h"
#include <unity.h>

#define REG_INIT_0 0x80
#define REG_INIT_1 0x80
#define REG_INIT_2 0x80

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
    TEST_ASSERT_EQUAL(REG_INIT_0, register_value[0]);
    TEST_ASSERT_EQUAL(REG_INIT_1, register_value[1]);
    TEST_ASSERT_EQUAL(REG_INIT_2, register_value[2]);
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

// void
// test_FindFunction_WhichIsBroken_ShouldReturnZeroIfItemIsNotInList_WhichWorksEvenInOurBrokenCode(void)
// {
//   /* All of these should pass */
//   TEST_ASSERT_EQUAL(0, FindFunction_WhichIsBroken(78));
//   TEST_ASSERT_EQUAL(0, FindFunction_WhichIsBroken(2));
//   TEST_ASSERT_EQUAL(0, FindFunction_WhichIsBroken(33));
//   TEST_ASSERT_EQUAL(0, FindFunction_WhichIsBroken(999));
//   TEST_ASSERT_EQUAL(0, FindFunction_WhichIsBroken(-1));
// }

// void
// test_FindFunction_WhichIsBroken_ShouldReturnTheIndexForItemsInList_WhichWillFailBecauseOurFunctionUnderTestIsBroken(void)
// {
//   /* You should see this line fail in your test summary */
//   TEST_ASSERT_EQUAL(1, FindFunction_WhichIsBroken(34));

//   /* Notice the rest of these didn't get a chance to run because the line
//   above failed.
//    * Unit tests abort each test function on the first sign of trouble.
//    * Then NEXT test function runs as normal. */
//   TEST_ASSERT_EQUAL(8, FindFunction_WhichIsBroken(888));
// }

// void
// test_FunctionWhichReturnsLocalVariable_ShouldReturnTheCurrentCounterValue(void)
// {
//     /* This should be true because setUp set this up for us before this test
//     */
//     TEST_ASSERT_EQUAL_HEX(Counter, FunctionWhichReturnsLocalVariable());

//     /* This should be true because we can still change our answer */
//     Counter = 0x1234;
//     TEST_ASSERT_EQUAL_HEX(0x1234, FunctionWhichReturnsLocalVariable());
// }

// void
// test_FunctionWhichReturnsLocalVariable_ShouldReturnTheCurrentCounterValueAgain(void)
// {
//     /* This should be true again because setup was rerun before this test
//     (and after we changed it to 0x1234) */
//     TEST_ASSERT_EQUAL_HEX(0x5a5a, FunctionWhichReturnsLocalVariable());
// }

// void
// test_FunctionWhichReturnsLocalVariable_ShouldReturnCurrentCounter_ButFailsBecauseThisTestIsActuallyFlawed(void)
// {
//     /* Sometimes you get the test wrong.  When that happens, you get a
//     failure too... and a quick look should tell
//      * you what actually happened...which in this case was a failure to setup
//      the initial condition. */
//     TEST_ASSERT_EQUAL_HEX(Counter, FunctionWhichReturnsLocalVariable());
// }

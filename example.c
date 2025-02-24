#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>

#include "crosscheck.h"

#define GEN_RAND_NUM rand() % (1024 + 1 - 0) + 0

static int undertest_x = 0;
static int undertest_y = 0;
static int expected = 0;

void
cc_setup()
{
    undertest_x = GEN_RAND_NUM;
    undertest_y = GEN_RAND_NUM;
    expected = undertest_x + undertest_y;
}

void
cc_tear_down()
{
    undertest_x = 0;
    undertest_y = 0;
    expected = 0;
}

int64_t
add(int64_t x, int64_t y)
{
    return x + y;
}

int64_t
sub(int64_t x, int64_t y)
{
    return x - y;
}

/* tests */

cc_result_t
test_add_fail()
{
    CC_ASSERT_NOT_EQUAL(add(2, 4), 5);
    CC_SUCCESS;
}

cc_result_t
test_add_success()
{
    CC_ASSERT_EQUAL(add(undertest_x, undertest_y), expected);
    CC_SUCCESS;
}

cc_result_t
test_sub_success()
{
    CC_ASSERT_EQUAL(sub(undertest_x, undertest_y), (undertest_x-undertest_y));
    CC_SUCCESS;
}

cc_result_t
test_string_compare_success()
{
    CC_ASSERT_STRING_EQUAL("y", "x");
    CC_SUCCESS;
}

cc_result_t
test_string_compare_failure()
{
    CC_ASSERT_STRING_NOT_EQUAL("x", "y");
    CC_SUCCESS;
}

int
main(void)
{
    srand(time(NULL));
    cc_init();
 
    cc_run(test_add_fail);
    cc_run(test_add_success);
    cc_run(test_sub_success);
    cc_run(test_string_compare_success);
    cc_run(test_string_compare_failure);

    cc_complete();

    return 0;
}

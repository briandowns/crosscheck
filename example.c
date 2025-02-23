#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "crosscheck.h"

int64_t
add(int64_t x, int64_t y)
{
    return x + y;
}

cc_result_t
test_add_fail()
{
    CC_ASSERT_NOT_EQUAL(add(2, 4), 5);
    CC_SUCCESS;
}

cc_result_t
test_add_success()
{
    CC_ASSERT_EQUAL(add(2, 4), 6);
    CC_SUCCESS;
}

int
main(void)
{
    cc_init();
 
    cc_run("add", test_add_fail);
    cc_run("add", test_add_success);

    cc_complete();

    return 0;
}

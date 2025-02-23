#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "crosscheck.h"

#define GREEN "\x1B[32m"
#define RED   "\x1B[31m"
#define RESET "\033[0m"

static clock_t start, end;
static uint64_t count = 0;
static uint64_t passed = 0;
static uint64_t failed = 0;
static clock_t start = 0;
static clock_t end = 0;

void
cc_init()
{
    start = clock();
    printf("Running test suite...\n"); 
}

bool
cc_run(cc_func_t func)
{
    cc_setup();

    count++;

    clock_t test_start = clock();
    cc_result_t ret = func();
    clock_t test_end = clock();

    double time_spent = (double)(test_end - test_start) / CLOCKS_PER_SEC;
    if (ret.result == false) {
        failed++;
        printf("    %-28s%-2s:%-21ld" RED "%-8s" RESET " %-2.3f/ms\n",
            ret.function, ret.filename, ret.line, "failed", (time_spent*1000));
        cc_tear_down();

        return false;
    }
    passed++;

    printf("    %-28s%-28s" GREEN "%-8s" RESET "   %-2.3f/ms\n",
        ret.function, "", "   passed", (time_spent*1000));
    cc_tear_down();

    return true;
}

void
cc_complete()
{
    end = clock();
    double ts = (double)(end - start) / CLOCKS_PER_SEC; \
    printf("\nTotal: %-4"PRIu64 " Passed: %-4lu Failed: %-4"PRIu64 "in  %-2.3f/ms\n", \
         count, passed, failed, (ts*1000));
}

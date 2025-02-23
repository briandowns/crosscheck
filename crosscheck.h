#ifdef __cplusplus
extern "C" {
#endif

#ifndef __CC_H
#define __CC_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

typedef struct {
    char *filename;
    bool result;
    uint64_t line;
} cc_result_t;

#define CC_SUCCESS return (cc_result_t) { \
    .filename = __FILE__, \
    .result = true, \
    .line = 0 \
};
#define CC_ASSERT(condition) return condition
#define CC_ASSERT_EQUAL(actual, expected) \
    do { \
        if (actual != expected) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)
#define CC_ASSERT_NOT_EQUAL(actual, expected) \
    do { \
        if (actual == expected) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)
#define CC_ASSERT_EQUAL_CHAR(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_STRING(actual, expected) \
    do { \
        if (strcmp(actual, expected) != 0) { \
            return false; \
        } \
    } while (0)
#define CC_ASSERT_EQUAL_SIZE_T(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_UINT8(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_UINT16(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_UINT32(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_UINT64(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_INT8(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_INT16(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_INT32(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_INT64(actual, expected) CC_ASSERT_EQUAL(actual, expected)
#define CC_ASSERT_EQUAL_INT(actual, expected) CC_ASSERT_EQUAL(actual, expected)

#define CC_COMPELETE \
    end = clock(); \
    double ts = (double)(end - start) / CLOCKS_PER_SEC; \
    printf("\nTotal: %-4"PRIu64 " Passed: %-4"PRIu64 " Failed: %-4"PRIu64 " in  %-2.3f/ms\n", \
         count, passed, failed, (ts*1000));

/**
 * cc_func_t is the function definition for a unit test to be passed into the
 * cc_run function for execution.
 */
typedef cc_result_t (*cc_func_t)();

/**
 * Initializes the library and needed memory.
 */
void
cc_init();

/**
 * Cleans up used resources and prints results.
 */
void
cc_complete();

/**
 * Run the given test. This function can be called but needs to have the
 * additional arguments filled in to work. It's advised for users to use
 * the macro defined below.
 */
bool
cc_run(const char *name, cc_func_t func);

#endif /* end __CC_H */
#ifdef __cplusplus
}
#endif

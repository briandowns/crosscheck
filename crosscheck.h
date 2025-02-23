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
    char *function;
    bool result;
    uint64_t line;
} cc_result_t;

#define CC_SUCCESS return (cc_result_t) { \
    .filename = __FILE__, \
    .function = (char*)__FUNCTION__, \
    .result = true, \
    .line = 0 \
};

#define CC_ASSERT_EQUAL(actual, expected) \
    do { \
        if (actual != expected) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .function = (char*)__FUNCTION__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)
#define CC_ASSERT_NOT_EQUAL(actual, expected) \
    do { \
        if (actual != expected) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .function = (char*)__FUNCTION__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)
#define CC_ASSERT_EQUAL_STRING(actual, expected) \
    do { \
        if (strcmp(actual, expected) != 0) { \
            return false; \
        } \
    } while (0)

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
cc_run(cc_func_t func);

#endif /* end __CC_H */
#ifdef __cplusplus
}
#endif

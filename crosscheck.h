/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2025 Brian J. Downs
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

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

typedef enum test_value_type {
    test_type_string,
    test_type_int,
    test_type_int8,
    test_type_int16,
    test_type_int32,
    test_type_int64,
    test_type_uint,
    test_type_uint8,
    test_type_uint16,
    test_type_uint32,
    test_type_uint64,
} test_value_type_t;

/**
 * cc_result_t holds the state of a test run, most importantly whether
 * the test has failed or succeeded.
 */
typedef struct {
    char *filename;
    char *function;
    test_value_type_t t;
    void *expected;
    void *actual;
    bool result;
    uint64_t line;
} cc_result_t;

/**
 * cc_func_t is the function definition for a unit test to be passed into the
 * cc_run function for execution.
 */
typedef cc_result_t (*cc_func_t)();

/**
 * CC_SUCCESS is a convenience macro to be included at the end of the 
 * test functions indicating a successful run.
 */
#define CC_SUCCESS return (cc_result_t) { \
    .function = (char*)__FUNCTION__,      \
    .result = true,                       \
};

/**
 * CC_ASSERT_EQUAL takes 2 comparable values and reports on their equality. 
 */
#define CC_ASSERT_EQUAL(actual, expected)        \
    do {                                         \
        if (actual != expected) {                \
            return (cc_result_t) {               \
                .filename = __FILE__,            \
                .function = (char*)__FUNCTION__, \
                .result = false,                 \
                .line = __LINE__                 \
            };                                   \
        }                                        \
    } while (0)

/**
 * CC_ASSERT_EQUAL takes 2 comparable values and reports on their equality. 
 */
#define CC_ASSERT_EQUAL_TYPE(actual, expected, type) \
do {                                         \
    if (actual != expected) {                \
        return (cc_result_t) {               \
            .filename = __FILE__,            \
            .function = (char*)__FUNCTION__, \
            .result = false,                 \
            .line = __LINE__                 \
        };                                   \
    }                                        \
} while (0)

/**
 * CC_ASSERT_NOT_EQUAL takes 2 comparable values and reports on
 * their inequality.
 */
#define CC_ASSERT_NOT_EQUAL(actual, expected) \
    do { \
        if (actual == expected) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .function = (char*)__FUNCTION__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)

#define CC_ASSERT_INT_EQUAL(actual, expected) CC_ASSERT_EQUAL(actual, expected)

/**
 * CC_ASSERT_STRING_EQUAL takes 2 strings and reports on their inequality. 
 */
#define CC_ASSERT_STRING_EQUAL(actual, expected) \
    do { \
        if (strcmp(actual, expected) != 0) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .function = (char*)__FUNCTION__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)

/**
 * CC_ASSERT_STRING_NOT_EQUAL takes 2 strings and reports on their inequality. 
 */
#define CC_ASSERT_STRING_NOT_EQUAL(actual, expected) \
    do { \
        if (strcmp(actual, expected) == 0) { \
            return (cc_result_t) { \
                .filename = __FILE__, \
                .function = (char*)__FUNCTION__, \
                .result = false, \
                .line = __LINE__ \
            }; \
        } \
    } while (0)

/**
 * cc_setup is a function that needs to be implemented by the consumer of the 
 * library and will be ran before every test.
 */
void
cc_setup();

/**
 * cc_tear_down is a function that needs to be implemented by the consumer of
 * the library and will be ran before every test.
 */
void
cc_tear_down();

/**
 * cc_init initializes the library and needed memory.
 */
void
cc_init();

#define CC_INIT cc_init();

/**
 * cc_complete cleans up used resources and prints results.
 */
uint64_t
cc_complete();

#define CC_COMPLETE return cc_complete();

/**
 * Run the given test.
 */
bool
cc_run(cc_func_t func);

#define CC_RUN(func) cc_run(func);

#endif /* end __CC_H */
#ifdef __cplusplus
}
#endif

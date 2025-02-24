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
    printf("Running tests...\n\n"); 
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
        printf("  %-28s%18s:%-12ld" RED "%-8s" RESET " %-2.3f/ms\n",
            ret.function, ret.filename, ret.line, "failed", (time_spent*1000));
        printf("        expected: x, got: y\n");
        cc_tear_down();

        return false;
    }
    passed++;
    
    printf("  %-28s%-28s" GREEN "%-8s" RESET "   %-2.3f/ms\n",
        ret.function, "", "   passed", (time_spent*1000));
    cc_tear_down();
    
    return true;
}

void
cc_complete()
{
    end = clock();
    double ts = (double)(end - start) / CLOCKS_PER_SEC; \
    printf("\nTotal: %-4"PRIu64 " Passed: %-4"PRIu64 " Failed: %-4"PRIu64 "in  %-2.3f/ms\n", \
         count, passed, failed, (ts*1000));
}

/*
 * The MIT License (MIT)
 *
 * Copyright © 2015 Franklin "Snaipe" Mathieu <http://snai.pe/>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef CRITERION_STATS_H_
# define CRITERION_STATS_H_

# include "types.h"

# ifdef __cplusplus
namespace criterion {
#  define CRITERION_STRUCT_ASSERT_STATS assert_stats
#  define CRITERION_STRUCT_TEST_STATS test_stats
#  define CRITERION_STRUCT_SUITE_STATS suite_stats
#  define CRITERION_STRUCT_GLOBAL_STATS global_stats
# else
#  define CRITERION_STRUCT_ASSERT_STATS criterion_assert_stats
#  define CRITERION_STRUCT_TEST_STATS criterion_test_stats
#  define CRITERION_STRUCT_SUITE_STATS criterion_suite_stats
#  define CRITERION_STRUCT_GLOBAL_STATS criterion_global_stats
# endif

struct CRITERION_STRUCT_ASSERT_STATS {
    int kind;
    const char *condition;
    const char *message;
    bool passed;
    unsigned line;
    const char *file;

# ifdef __cplusplus
    ::criterion::assert_stats *next;
# else
    struct criterion_assert_stats *next;
# endif
};

struct CRITERION_STRUCT_TEST_STATS {
# ifdef __cplusplus
    ::criterion::test *test;
    ::criterion::assert_stats *asserts;
# else
    struct criterion_test *test;
    struct criterion_assert_stats *asserts;
# endif
    bool failed;
    int passed_asserts;
    int failed_asserts;
    int signal;
    float elapsed_time;
    unsigned progress;
    const char *file;

# ifdef __cplusplus
    ::criterion::test_stats *next;
# else
    struct criterion_test_stats *next;
# endif
};

struct CRITERION_STRUCT_SUITE_STATS {
# ifdef __cplusplus
    ::criterion::suite *suite;
    ::criterion::test_stats *tests;
# else
    struct criterion_suite *suite;
    struct criterion_test_stats *tests;
# endif
    size_t nb_tests;
    size_t nb_asserts;
    size_t tests_skipped;
    size_t tests_failed;
    size_t tests_crashed;
    size_t tests_passed;
    size_t asserts_failed;
    size_t asserts_passed;

# ifdef __cplusplus
    ::criterion::suite_stats *next;
# else
    struct criterion_suite_stats *next;
# endif
};

struct CRITERION_STRUCT_GLOBAL_STATS {
# ifdef __cplusplus
    ::criterion::suite_stats *suites;
# else
    struct criterion_suite_stats *suites;
# endif
    size_t nb_suites;
    size_t nb_tests;
    size_t nb_asserts;
    size_t tests_skipped;
    size_t tests_failed;
    size_t tests_crashed;
    size_t tests_passed;
    size_t asserts_failed;
    size_t asserts_passed;
};

# ifdef __cplusplus
}
# endif

#endif /* !CRITERION_STATS_H_ */

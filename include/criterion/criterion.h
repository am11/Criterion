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
#ifndef CRITERION_H_
# define CRITERION_H_

# include "common.h"
# include "assert.h"
# include "types.h"

# ifdef __cplusplus
#  include "designated_initializer_compat.h"
# endif

# define IDENTIFIER_(Category, Name, Suffix) \
    Category ## _ ## Name ## _ ## Suffix
# define TEST_PROTOTYPE_(Category, Name) \
    void IDENTIFIER_(Category, Name, impl)(void)

# define SUITE_IDENTIFIER_(Name, Suffix) \
    cr_suite_ ## Name ## _ ## Suffix

# define Test(...) Test_(__VA_ARGS__, .sentinel_ = 0)
# ifdef __cplusplus
#  define Test_(Category, Name, ...)                                           \
    extern "C" TEST_PROTOTYPE_(Category, Name);                                \
    ::criterion::test_extra_data IDENTIFIER_(Category, Name, gen_extra)() {    \
        ::criterion::test_extra_data data;                                     \
        data.identifier_ = #Category "/" #Name;                                \
        data.file_    = __FILE__;                                              \
        data.line_    = __LINE__;                                              \
        CRITERION_ADD_PREFIX(data, __VA_ARGS__)                                \
        return data;                                                           \
    }                                                                          \
    ::criterion::test_extra_data IDENTIFIER_(Category, Name, extra) =          \
        IDENTIFIER_(Category, Name, gen_extra)();                              \
    ::criterion::test IDENTIFIER_(Category, Name, gen_test)() {                \
        ::criterion::test test;                                                \
        test.name     = #Name;                                                 \
        test.category = #Category;                                             \
        test.test     = IDENTIFIER_(Category, Name, impl);                     \
        test.data     = &IDENTIFIER_(Category, Name, extra);                   \
        return test;                                                           \
    }                                                                          \
    SECTION_("cr_tst")                                                         \
    ::criterion::test IDENTIFIER_(Category, Name, meta) =                      \
        IDENTIFIER_(Category, Name, gen_test)();                               \
    extern "C" TEST_PROTOTYPE_(Category, Name)
# else
#  define Test_(Category, Name, ...)                                            \
    TEST_PROTOTYPE_(Category, Name);                                           \
    struct criterion_test_extra_data IDENTIFIER_(Category, Name, extra) = {    \
        .identifier_ = #Category "/" #Name,                                    \
        .file_    = __FILE__,                                                  \
        .line_    = __LINE__,                                                  \
        __VA_ARGS__                                                            \
    };                                                                         \
    SECTION_("cr_tst")                                                         \
    const struct criterion_test IDENTIFIER_(Category, Name, meta) = {          \
        .name     = #Name,                                                     \
        .category = #Category,                                                 \
        .test     = IDENTIFIER_(Category, Name, impl),                         \
        .data     = &IDENTIFIER_(Category, Name, extra)                        \
    };                                                                         \
    TEST_PROTOTYPE_(Category, Name)
# endif

# define TestSuite(...) TestSuite_(__VA_ARGS__, .sentinel_ = 0)
# ifdef __cplusplus
#  define TestSuite_(Name, ...)                                                \
    ::criterion::test_extra_data SUITE_IDENTIFIER_(Name, gen_extra)() {        \
        ::criterion::test_extra_data data;                                     \
        data.file_    = __FILE__;                                              \
        data.line_    = 0;                                                     \
        CRITERION_ADD_PREFIX(data, __VA_ARGS__)                                \
        return data;                                                           \
    }                                                                          \
    ::criterion::test_extra_data SUITE_IDENTIFIER_(Name, extra) =              \
        SUITE_IDENTIFIER_(Name, gen_extra)();                                  \
    ::criterion::test IDENTIFIER_(Category, Name, gen_suite)() {               \
        ::criterion::suite suite;                                              \
        suite.name     = #Name;                                                \
        suite.data     = &SUITE_IDENTIFIER_(Name, extra);                      \
        return suite;                                                          \
    }                                                                          \
    SECTION_("cr_sts")                                                         \
    ::criterion::suite SUITE_IDENTIFIER_(Name, meta) =                         \
        SUITE_IDENTIFIER_(Name, gen_suite)();                                  \
    extern "C" TEST_PROTOTYPE_(Category, Name)
# else
#  define TestSuite_(Name, ...)                                                \
    struct criterion_test_extra_data SUITE_IDENTIFIER_(Name, extra) = {        \
        .file_    = __FILE__,                                                  \
        .line_    = 0,                                                         \
        __VA_ARGS__                                                            \
    };                                                                         \
    SECTION_("cr_sts")                                                         \
    const struct criterion_suite SUITE_IDENTIFIER_(Name, meta) = {             \
        .name     = #Name,                                                     \
        .data     = &SUITE_IDENTIFIER_(Name, extra),                           \
    }
# endif

# ifdef __cplusplus
extern "C" {
# endif

int criterion_run_all_tests(void);

# ifdef __cplusplus
}

namespace criterion {
    int (&run_all_tests)(void) = criterion_run_all_tests;
}
# endif

#endif /* !CRITERION_H_ */

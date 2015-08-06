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
#ifndef CRITERION_TYPES_H_
# define CRITERION_TYPES_H_

# ifndef __cplusplus
#  include <stdbool.h>
#  include <stddef.h>
#  define CRITERION_STRUCT_TEST_EXTRA_DATA criterion_test_extra_data
#  define CRITERION_STRUCT_TEST criterion_test
#  define CRITERION_STRUCT_SUITE criterion_suite
# else
#  include <cstddef>
#  define CRITERION_STRUCT_TEST_EXTRA_DATA test_extra_data
#  define CRITERION_STRUCT_TEST test
#  define CRITERION_STRUCT_SUITE suite
# endif
# include "common.h"

# ifdef __cplusplus
namespace criterion {
# endif

struct CRITERION_STRUCT_TEST_EXTRA_DATA {
    const char *identifier_;
    const char *file_;
    unsigned line_;
    void (*init)(void);
    void (*fini)(void);
    int signal;
    bool disabled;
    const char *description;
    void *data;
    int sentinel_;
};

struct CRITERION_STRUCT_TEST {
    const char *name;
    const char *category;
    void (*test)(void);
# ifndef __cplusplus
    struct criterion_test_extra_data *data;
# else
    test_extra_data *data;
# endif
};

struct CRITERION_STRUCT_SUITE {
    const char *name;
# ifndef __cplusplus
    struct criterion_test_extra_data *data;
# else
    test_extra_data *data;
# endif
};

# ifndef __cplusplus
typedef void (*f_worker_func)(struct criterion_test *, struct criterion_suite *);
# else
typedef void (*f_worker_func)(criterion::test *, criterion::suite *);
# endif

# ifdef __cplusplus
}
# endif

#endif /* !CRITERION_TYPES_H_ */

#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>

#define debug_error(c, ...) { \
        fprintf(stderr, "An unexpected error occured in function '%s' :\n", c); \
        fprintf(stderr, __VA_ARGS__); \
    }

#endif
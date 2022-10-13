#ifndef __DEBUG_H__
#define __DEBUG_H__

#define debug_error(c, f, ...) { \
        fprintf(stderr, "An unexpected error occured in function '%s' :\n", c); \
        fprintf(stderr, f, __VA_ARGS__); \
    }

#endif
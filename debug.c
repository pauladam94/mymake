#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "debug.h"

/*
debug_error : given a context, a formated string, and more optional parameters, it prints an explicit error message to stderr
*/
void debug_error(char *context, char *format, ...) {
    va_list ptr;

    va_start(ptr, format);

    fprintf(stderr, "Unexpected error occured in function '%s' :\n", context);
    fprintf(stderr, format, ptr);

    va_end(ptr);
}
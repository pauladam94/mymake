#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "debug.h"

void debug_error(char *context, char *format, ...) {
    va_list ptr;

    va_start(ptr, format);

    fprintf(stderr, "Unexpected error in function '%s' : ", context);
    fprintf(stderr, format, ptr);

    va_end(ptr);
}
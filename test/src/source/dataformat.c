
#include "dataformat.h"

unsigned char *data_format(const char *__restrict__ format, ...)
{
    char *__restrict__ value;

    va_list parameter_pointer;
    va_start(parameter_pointer, format);

    vsprintf(value, format, parameter_pointer);

    va_end(parameter_pointer);

    return value;
}

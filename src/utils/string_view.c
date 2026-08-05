#include "include/utils/string_view.h"

#include <string.h>

string_view_t string_view_from(const char* string)
{
    return (string_view_t) {
        .string = string,
        .length = strlen(string)
    };
}

#ifndef PESEC_VALUE_H
#define PESEC_VALUE_H

#include "utils/string_view.h"

typedef enum
{
    VALUE_TYPE_STRING,
    VALUE_TYPE_NUMBER,
    // TODO: VALUE_TYPE_FUNCTION,
} value_type_t;

typedef union
{
    string_view_t as_string;
    long double as_number;
} value_value_t;

typedef struct
{
    value_type_t type;
    value_value_t value;
} value_t;

value_t value_operation_add(value_t left, value_t right);

value_t value_operation_sub(value_t left, value_t right);

value_t value_operation_mul(value_t left, value_t right);

value_t value_operation_div(value_t left, value_t right);

#endif // PESEC_VALUE_H

#include "include/value.h"

#include <stdio.h>
#include <stdlib.h>


value_t value_operation_add(const value_t left, const value_t right)
{
    if (left.type == VALUE_TYPE_NUMBER && right.type == VALUE_TYPE_NUMBER)
        return (value_t) {
            .type = VALUE_TYPE_NUMBER,
            .value.as_number = left.value.as_number + right.value.as_number,
        };

    fprintf(stderr, "Non number type can't use operator '+'\n");
    exit(EXIT_FAILURE);
}

value_t value_operation_sub(const value_t left, const value_t right)
{
    if (left.type == VALUE_TYPE_NUMBER && right.type == VALUE_TYPE_NUMBER)
        return (value_t) {
            .type = VALUE_TYPE_NUMBER,
            .value.as_number = left.value.as_number - right.value.as_number,
        };

    fprintf(stderr, "Non number type can't use operator '-'\n");
    exit(EXIT_FAILURE);
}

value_t value_operation_mul(const value_t left, const value_t right)
{
    if (left.type == VALUE_TYPE_NUMBER && right.type == VALUE_TYPE_NUMBER)
        return (value_t) {
            .type = VALUE_TYPE_NUMBER,
            .value.as_number = left.value.as_number * right.value.as_number,
        };

    fprintf(stderr, "Non number type can't use operator '*'\n");
    exit(EXIT_FAILURE);
}

value_t value_operation_div(const value_t left, const value_t right)
{
    // please never use right equal 0
    if (left.type == VALUE_TYPE_NUMBER && right.type == VALUE_TYPE_NUMBER)
        return (value_t) {
            .type = VALUE_TYPE_NUMBER,
            .value.as_number = left.value.as_number + right.value.as_number,
        };

    fprintf(stderr, "Non number type can't use operator '/'\n");
    exit(EXIT_FAILURE);
}
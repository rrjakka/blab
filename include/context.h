#ifndef PESEC_CONTEXT_H
#define PESEC_CONTEXT_H
#include "value.h"
#include "utils/string_view.h"

typedef struct CONTEXT_ITEM_STRUCT
{
    string_view_t key;
    value_t value;
    struct CONTEXT_ITEM_STRUCT* next;
} context_item_t;

typedef struct
{
    context_item_t** items;
    unsigned long long size;
    unsigned long long capacity;
} context_t;


context_t* context_new();

unsigned long long context_hash(const context_t* context, string_view_t key);

void context_push(const context_t* context, string_view_t key, value_t value);

void context_set(const context_t* context, string_view_t key, value_t value);

context_item_t* context_get(const context_t* context, string_view_t key);

void context_free(context_t* context);

#endif // PESEC_CONTEXT_H

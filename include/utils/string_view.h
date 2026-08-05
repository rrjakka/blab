#ifndef PESEC_STRING_VIEW_H
#define PESEC_STRING_VIEW_H

typedef struct
{
    const char* string;
    unsigned int length;
} string_view_t;

string_view_t string_view_from(const char* string);

#endif // PESEC_STRING_VIEW_H

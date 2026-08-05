#include <stdio.h>
#include <stdlib.h>

#include "include/lexer.h"
#include "include/parser.h"
#include "include/context.h"


void test_context()
{
    context_t* context = context_new();

    context_push(context, (string_view_t){.string="a10", .length=3}, 5.f);
    context_push(context, (string_view_t){.string="a01", .length=3}, 9.f);

    const context_item_t* a10 = context_get(context, (string_view_t){.string="a10", .length=3});
    const context_item_t* a01 = context_get(context, (string_view_t){.string="a01", .length=3});

    printf("%.*s = %Lf\n", a10->key.length, a10->key.string, a10->value);
    printf("%.*s = %Lf\n", a01->key.length, a01->key.string, a01->value);

    context_free(context);
}

int main(const int argc, char** argv)
{
    test_context();

    return EXIT_SUCCESS;

    if (argc < 2)
    {
        printf("Usage: pesec <file>\n");
        return EXIT_SUCCESS;
    }

    const char* filename = argv[1];
    char* source = nullptr;
    unsigned long long source_size = 0;

    FILE* file = fopen(filename, "r");

    if (!file)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
        return EXIT_FAILURE;
    }

    fseek(file, 0, SEEK_END);
    source_size = ftell(file);
    fseek (file, 0, SEEK_SET);
    source = (char*)malloc(source_size);
    fread(source, 1, source_size, file);
    fclose(file);

    lexer_t* lexer = lexer_new(source, source_size);
    parser_t* parser = parser_new(lexer);
    ast_node_t* ast = parser_parse(parser);

    const value_t result = ast_node_evaluate(ast);

    // TODO: надо б сделать заебатый контекст

    ast_node_free(ast);
    lexer_free(lexer);
    parser_free(parser);

    printf("finished with %Lf", result);

    return EXIT_SUCCESS;
}

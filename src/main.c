#include <stdio.h>
#include <stdlib.h>

#include "include/lexer.h"
#include "include/parser.h"


int main(const int argc, char** argv)
{
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

    printf("finnished with %Lf", result);

    return EXIT_SUCCESS;
}

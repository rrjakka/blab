#include <stdio.h>
#include <string.h>

#include "include/lexer.h"
#include "include/parser.h"


int main()
{
    const auto source = "(2 + 1) * 5 * 2";

    lexer_t* lexer = lexer_new(source, strlen(source));
    parser_t* parser = parser_new(lexer);
    ast_node_t* ast = parser_parse(parser);

    printf("%s = %Lf\n", source, ast_node_evaluate(ast));

    ast_node_free(ast);
    lexer_free(lexer);
    parser_free(parser);

    printf("finnish!");

    return 0;
}

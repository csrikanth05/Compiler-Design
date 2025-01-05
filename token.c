#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 1000

typedef enum {
    IDENTIFIER,
    KEYWORD,
    NUMBER,
    OPERATOR,
    SEPARATOR,
    UNKNOWN
} TokenType;

const char *keywords[] = {
    "auto", "break", "case", "char", "const", "continue", "default", "do",
    "double", "else", "enum", "extern", "float", "for", "goto", "if",
    "int", "long", "register", "return", "short", "signed", "sizeof",
    "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"
};

int is_keyword(const char *word) {
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++) {
        if (strcmp(word, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

TokenType classify(const char *token) {
    if (is_keyword(token)) {
        return KEYWORD;
    } else if (isdigit(token[0])) {
        return NUMBER;
    } else if (isalpha(token[0]) || token[0] == '_') {
        return IDENTIFIER;
    } else if (strchr("+-*/%=&|!<>^", token[0]) != NULL) {
        return OPERATOR;
    } else if (strchr(",;(){}[]", token[0]) != NULL) {
        return SEPARATOR;
    }
    return UNKNOWN;
}

const char* get_token_type(TokenType type) {
    switch (type) {
        case IDENTIFIER: return "Identifier";
        case KEYWORD: return "Keyword";
        case NUMBER: return "Number";
        case OPERATOR: return "Operator";
        case SEPARATOR: return "Separator";
        case UNKNOWN: return "Unknown";
    }
    return "Unknown";
}

void tokenize(const char *code) {
    char buffer[MAX_LENGTH];
    strncpy(buffer, code, MAX_LENGTH - 1);
    buffer[MAX_LENGTH - 1] = '\0';

    char *token = strtok(buffer, " \t\n");
    while (token != NULL) {
        TokenType type = classify(token);
        printf("Token: %-15s Type: %s\n", token, get_token_type(type));
        token = strtok(NULL, " \t\n");
    }
}

int main() {
    char code[MAX_LENGTH];

    printf("Enter a C code snippet:\n");
    if (fgets(code, MAX_LENGTH, stdin) != NULL) {
        tokenize(code);
    }

    return 0;
}

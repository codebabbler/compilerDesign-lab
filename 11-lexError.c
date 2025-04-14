#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TOKEN_SIZE 100
#define INPUT_SIZE 200

int isValidOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' ||
           ch == '=' || ch == '(' || ch == ')';
}

int isDelimiter(char ch) {
    return isspace(ch) || isValidOperator(ch);
}

int isValidIdentifier(const char *token) {
    if (!isalpha(token[0]) && token[0] != '_')
        return 0;
    for (int i = 1; token[i]; i++) {
        if (!isalnum(token[i]) && token[i] != '_')
            return 0;
    }
    return 1;
}

int isValidNumber(const char *token) {
    int dotCount = 0;
    for (int i = 0; token[i]; i++) {
        if (token[i] == '.') {
            dotCount++;
            if (dotCount > 1)
                return 0;
        } else if (!isdigit(token[i])) {
            return 0;
        }
    }
    return 1;
}

// Helper function to process a token and report any lexical errors.
// errorFound is incremented if an error is detected.
void processToken(const char *token, int *errorFound) {
    if (token[0] == '\0') {
        return; // Skip empty tokens.
    }
    
    int hasAlpha = 0;
    for (int k = 0; token[k]; k++) {
        if (isalpha(token[k])) {
            hasAlpha = 1;
            break;
        }
    }
    
    if (isdigit(token[0])) {
        if (hasAlpha) {
            printf("Lexical Error: Invalid identifier '%s' (starts with digit).\n", token);
            (*errorFound)++;
        } else if (!isValidNumber(token)) {
            printf("Lexical Error: Invalid number '%s'.\n", token);
            (*errorFound)++;
        }
    } else if (isalpha(token[0]) || token[0] == '_') {
        if (!isValidIdentifier(token)) {
            printf("Lexical Error: Invalid identifier '%s'.\n", token);
            (*errorFound)++;
        }
    } else {
        printf("Lexical Error: Unknown token '%s'.\n", token);
        (*errorFound)++;
    }
}

void reportLexicalErrors(char *input) {
    char token[TOKEN_SIZE];
    int i = 0, j = 0;
    int errorFound = 0;

    while (input[i] != '\0') {
        if (isDelimiter(input[i])) {
            if (j != 0) {
                token[j] = '\0';
                processToken(token, &errorFound);
                j = 0;
            }

            // Handle single-character operators
            if (isValidOperator(input[i])) {
                // Operators are valid tokens on their own; you can process them if needed.
                // For now, we treat them as valid, so no error is reported.
            } else if (!isspace(input[i])) {
                printf("Lexical Error: Invalid character '%c'\n", input[i]);
                errorFound++;
            }
            i++;
        } else {
            // Accumulate characters for a token.
            token[j++] = input[i++];
        }
    }

    // Process the last token if any.
    if (j != 0) {
        token[j] = '\0';
        processToken(token, &errorFound);
    }

    if (errorFound == 0)
        printf("No lexical errors found.\n");
}

int main() {
    char input[INPUT_SIZE];

    printf("Enter the input string: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; 

    reportLexicalErrors(input);
    return 0;
}

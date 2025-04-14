#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char result[10], op1[10], op[5], op2[10];
} Statement;

typedef struct {
    char name[10];
    int value;
    int valid; // 1 = valid constant, 0 = non-constant
} Constant;

// Checks if the given string is a number (only digits)
int isNumber(const char *str) {
    for (int i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

// Searches for a constant in the table.
// Returns 1 and assigns the value to *val if found and valid, otherwise returns 0.
int getConstantValue(Constant constTable[], int count, const char *name, int *val) {
    for (int i = 0; i < count; i++) {
        if (strcmp(constTable[i].name, name) == 0 && constTable[i].valid) {
            *val = constTable[i].value;
            return 1;
        }
    }
    return 0;
}

// Evaluates the operator on two integer operands.
int compute(const char *op, int val1, int val2) {
    if (strcmp(op, "+") == 0) return val1 + val2;
    if (strcmp(op, "-") == 0) return val1 - val2;
    if (strcmp(op, "*") == 0) return val1 * val2;
    if (strcmp(op, "/") == 0 && val2 != 0) return val1 / val2;
    return 0; // Default or error: division by zero could be handled more gracefully.
}

// Adds a new constant entry to the constant table.
void addConstant(Constant constTable[], int *constCount, const char *name, int value, int valid) {
    strcpy(constTable[*constCount].name, name);
    constTable[*constCount].value = value;
    constTable[*constCount].valid = valid;
    (*constCount)++;
}

// Processes an operand by checking if it's a number or a constant from the table.
// If the operand is constant, it assigns the value to outVal and returns 1.
int processOperand(const char operand[], Constant constTable[], int constCount, int *outVal) {
    if (isNumber(operand)) {
        *outVal = atoi(operand);
        return 1;
    } else if (getConstantValue(constTable, constCount, operand, outVal)) {
        return 1;
    }
    return 0;
}

int main() {
    Statement stmts[MAX];
    Constant constTable[MAX];
    int n;

    printf("Enter number of statements: ");
    scanf("%d", &n);
    getchar(); // consume newline after number input

    // Input intermediate code statements
    for (int i = 0; i < n; i++) {
        printf("Enter statement %d (e.g., t1 = a + b): ", i + 1);
        scanf("%s = %s %s %s", stmts[i].result, stmts[i].op1, stmts[i].op, stmts[i].op2);
    }

    printf("\nAfter Constant Folding and Propagation:\n");

    int constCount = 0; // Number of entries in constant table

    for (int i = 0; i < n; i++) {
        int val1, val2;
        int isConst1 = processOperand(stmts[i].op1, constTable, constCount, &val1);
        int isConst2 = processOperand(stmts[i].op2, constTable, constCount, &val2);

        // If both operands are constants then fold the expression
        if (isConst1 && isConst2) {
            int result = compute(stmts[i].op, val1, val2);
            printf("%s = %d\n", stmts[i].result, result);
            addConstant(constTable, &constCount, stmts[i].result, result, 1);
        } else {
            // Otherwise, propagate the constant if possible
            char left[10], right[10];

            if (isConst1)
                sprintf(left, "%d", val1);
            else
                strcpy(left, stmts[i].op1);

            if (isConst2)
                sprintf(right, "%d", val2);
            else
                strcpy(right, stmts[i].op2);

            printf("%s = %s %s %s\n", stmts[i].result, left, stmts[i].op, right);
            addConstant(constTable, &constCount, stmts[i].result, 0, 0);  // Mark as non-constant
        }
    }

    return 0;
}

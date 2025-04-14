%{
#include <stdio.h>

int vowels = 0;
int consonants = 0;

int yywrap(void) { return 1; }
%}

%%

[aAeEiIoOuU] { vowels++; }
[b-df-hj-np-tv-z] { consonants++; }
[B-DF-HJ-NP-TV-Z] { consonants++; }

. { /* Ignore other characters */ }

\n { return 0; }  
%%

int main() {
    printf("Enter a string: ");
    yylex();

    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}

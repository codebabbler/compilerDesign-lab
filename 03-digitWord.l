%{
    /* To check if a given string is a word, a number, or something else */
    #include <stdio.h>
    
    void display(char[], int);
    int flag;
    
    int yywrap(void) { return 1; }  
%}

%%

[a-zA-Z]+ {
    flag = 1;
    display(yytext, flag);
    return 0;
}

[0-9]+ {
    flag = 0;
    display(yytext, flag);
    return 0;
}

.+ {
    flag = -1;
    display(yytext, flag);
    return 0;
}

%%

void display(char a[], int flag) {
    if (flag == 1)
        printf("The entered string \"%s\" is a word.\n", a);
    else if (flag == 0)
        printf("The entered string \"%s\" is a digit.\n", a);
    else
        printf("The entered string \"%s\" contains a mix of characters.\n", a);
}    

int main() {
    printf("Enter a string: ");
    yylex();
    return 0;
}

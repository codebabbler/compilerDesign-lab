%{
    /* To check whether the given letter is a vowel or not */
    #include <stdio.h>

    void display(int);
    int yywrap(void) { return 1; }  
%}

%%

[aeiouAEIOU] { 
    int flag = 1;
    display(flag);
    return 0; 
}

. { 
    int flag = 0;
    display(flag);
    return 0; 
}

%%

void display(int flag) {
    if (flag == 1)
        printf("The entered letter [%s] is a vowel.\n", yytext);
    else
        printf("The entered letter [%s] is not a vowel.\n", yytext);        
}

int main() {
    printf("Enter a letter to check if it is a vowel or not: ");
    yylex(); 
    return 0;
}

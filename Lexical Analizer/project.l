%{
#include<stdio.h>
%}
letter      [A-Z]
digit       [0-9]
whitespace  [ \t\r]+
keyword     #START|#END|DECLARE|ASSIGN|ANSWERS|RESULT
id          {letter}{digit}
operation   ADD|SUB|MUL|DIV
word        {letter}+
number      {digit}+(\.{digit}+)?
eol         [\.?]?{whitespace}?[\n]+
comment     "**"[^\n]*
%%
{keyword}   { printf("<Keyword : \'%s\'>,\n", yytext); }
{operation} { printf("<Operation : \'%s\'>,\n", yytext); }
{id}        { printf("<Id : \'%s\'>,\n", yytext); }
{word}      { printf("<Word : \'%s\'>,\n", yytext); }
{number}    { printf("<Number : \'%s\'>,\n", yytext); }
{eol}       { printf("<End of line>,\n"); }
{comment}   { printf("<Comment : \'%s\'>,\n", yytext+2); }
{whitespace} { }
.           { printf("<Invalid symbol : \'%s\'>,\n", yytext); }

%%

int yywrap(){ }

void main(int argc, char *argv[]){
    if(argc != 2){
        printf("Enter this way please : ./a.out filename\n");
        exit(0);
    }
    extern FILE *yyin;
    yyin = fopen(argv[1], "r");
    yylex();
    printf("\n");
}
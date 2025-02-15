%{
#include <stdio.h>
%}
%%
0(10)* printf("a") ;
1*(01)* printf("b") ;
(00|11)* printf("c") ;
[^2-9 \n]{2,5} printf("d") ;
%%
int yywrap() {
    return 1;  // Indicate no more input
}
int main() {
    yylex();
    return 0;
}
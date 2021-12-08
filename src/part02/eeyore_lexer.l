%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"eeyore_ast.hpp"
    #include"eeyore_parser.tab.hpp"
%}
%option yylineno

digit_10   [0-9]
var_T   T[0-9]+
var_t   t[0-9]+
var_p   p[0-9]+
letter  [a-zA-Z_]
fname    f_({letter}|{digit_10})*
label    l{digit_10}+
number  {digit_10}+ 

%%
[ \r\n\t]   {   if(Debug_Lex)   printf("Whitespace, Ignored!, lineno is %d\n", yylineno);}

    /*类型关键字*/
var     {   if(Debug_Lex)   printf("Recognized type keyword var, lineno is %d\n", yylineno);
            return VAR;
        }

    /*控制流关键字*/
if      {   if(Debug_Lex)   printf("Recognized control flow keyword IF, lineno is %d\n", yylineno);
            return IF;
        }

goto    {   if(Debug_Lex)   printf("Recognized control flow keyword GOTO, lineno is %d\n", yylineno);
            return GOTO;
        }

{label}    {   if(Debug_Lex)   printf("Recognized control flow keyword LABEL, lineno is %d\n", yylineno);
                    return LABEL;
                }

return      {   if(Debug_Lex)   printf("Recognized control flow keyword RETURN, lineno is %d\n", yylineno);
                return RETURN;
            }

    /*函数关键字*/
{fname}    {   if(Debug_Lex)   printf("Recognized function name, lineno is %d\n", yylineno);
                    return FNAME;
                }

call    {   if(Debug_Lex)   printf("Recognized function call, lineno is %d\n", yylineno);
            return CALL;
        }

param   {   if(Debug_Lex)   printf("Recognized function param, lineno is %d\n", yylineno);
            return PARAM;
        }

end   {   if(Debug_Lex)   printf("Recognized function end, lineno is %d\n", yylineno);
            return END;
        }

    /*运算符*/

"+"|"-"|"*"|"/"|"%"|"!"|"&&"|"||"|"<"|"<="|">"|">="|"=="|"!="     {
           if(Debug_Lex)   printf("Recognized Operator %s, lineno is %d\n", yytext, yylineno);
            yylval.kToken = new Token(Op, yytext, yylineno);
            return Op;
        }


"="         {   if(Debug_Lex)   printf("Recognized Operator ASSIGN, lineno is %d\n", yylineno);
                return ASSIGN;
            }

    /*标点符号*/

"["         {   if(Debug_Lex)   printf("Recognized Operator LKHZ, lineno is %d\n", yylineno);
                return LKHZ;
            }
"]"         {   if(Debug_Lex)   printf("Recognized Operator RKHZ, lineno is %d\n", yylineno);
                return RKHZ;
            }
":"         {   if(Debug_Lex)   printf("Recognized Operator COLON, lineno is %d\n", yylineno);
                return COLON;
            }

    /*标识符*/
{var_T}    {    if(Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", yytext, yylineno);
                yylval.kToken = new Token (SYMBOL, yytext, yylineno);
                return SYMBOL;
            }

{var_t}    {    if(Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", yytext, yylineno);
                yylval.kToken = new Token (SYMBOL, yytext, yylineno);
                return SYMBOL;
            }

{var_p}    {    if(Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", yytext, yylineno);
                yylval.kToken = new Token (SYMBOL, yytext, yylineno);
                return SYMBOL;
            }

    /*常量*/
{number}    {   int num = int(strtol(yytext, nullptr, 10));
                if(Debug_Lex)   printf("Recognized Literal %d, lineno is %d\n", num, yylineno);
                yylval.kToken = new Token (NUM, num, yylineno);
                return NUM;
            }


"//".*$     {  if(Debug_Lex)    printf("Comments, Ignored!");}
"/*"[^"*"]*(\*+[^"*/"][^"*"]*)*\*+"/"  { if(Debug_Lex)    printf("Comments, Ignored!");}

    /*其它情况直接返回*/
.           {   if(Debug_Lex)    printf("Other Cases: %s, lineno is %d\n", yytext, yylineno);
                return yytext[0];
            }

%%

int yywrap(void){
    return 1;
}
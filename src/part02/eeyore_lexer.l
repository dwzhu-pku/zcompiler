%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"eeyore_ast.hpp"
    #include"eeyore_parser.tab.hpp"
%}
%option yylineno
%option prefix="e2t_yy"

digit_10   [0-9]
var_T   T[0-9]+
var_t   t[0-9]+
var_p   p[0-9]+
letter  [a-zA-Z_]
fname    f_({letter}|{digit_10})*
label    l{digit_10}+
number  {digit_10}+ 

%%
[ \r\n\t]   {   if(E2T_Debug_Lex)   printf("Whitespace, Ignored!, lineno is %d\n", e2t_yylineno);}

    /*类型关键字*/
var     {   if(E2T_Debug_Lex)   printf("Recognized type keyword var, lineno is %d\n", e2t_yylineno);
            return VAR;
        }

    /*控制流关键字*/
if      {   if(E2T_Debug_Lex)   printf("Recognized control flow keyword IF, lineno is %d\n", e2t_yylineno);
            return IF;
        }

goto    {   if(E2T_Debug_Lex)   printf("Recognized control flow keyword GOTO, lineno is %d\n", e2t_yylineno);
            return GOTO;
        }

{label}    {   if(E2T_Debug_Lex)   printf("Recognized control flow keyword LABEL, lineno is %d\n", e2t_yylineno);
                e2t_yylval.kToken = new E2T_Token(LABEL, e2t_yytext, e2t_yylineno);
                return LABEL;
            }

return      {   if(E2T_Debug_Lex)   printf("Recognized control flow keyword RETURN, lineno is %d\n", e2t_yylineno);
                return RETURN;
            }

    /*函数关键字*/
{fname}    {   if(E2T_Debug_Lex)   printf("Recognized function name, lineno is %d\n", e2t_yylineno);
                e2t_yylval.kToken = new E2T_Token(FNAME, e2t_yytext, e2t_yylineno);
                return FNAME;
            }

call    {   if(E2T_Debug_Lex)   printf("Recognized function call, lineno is %d\n", e2t_yylineno);
            return CALL;
        }

param   {   if(E2T_Debug_Lex)   printf("Recognized function param, lineno is %d\n", e2t_yylineno);
            return PARAM;
        }

end   {   if(E2T_Debug_Lex)   printf("Recognized function end, lineno is %d\n", e2t_yylineno);
            return END;
        }

    /*运算符*/

"+"|"-"|"*"|"/"|"%"|"!"|"&&"|"||"|"<"|"<="|">"|">="|"=="|"!="     {
           if(E2T_Debug_Lex)   printf("Recognized Operator %s, lineno is %d\n", e2t_yytext, e2t_yylineno);
            e2t_yylval.kToken = new E2T_Token(Op, e2t_yytext, e2t_yylineno);
            return Op;
        }


"="         {   if(E2T_Debug_Lex)   printf("Recognized Operator ASSIGN, lineno is %d\n", e2t_yylineno);
                return ASSIGN;
            }

    /*标点符号*/

"["         {   if(E2T_Debug_Lex)   printf("Recognized Operator LKHZ, lineno is %d\n", e2t_yylineno);
                return LKHZ;
            }
"]"         {   if(E2T_Debug_Lex)   printf("Recognized Operator RKHZ, lineno is %d\n", e2t_yylineno);
                return RKHZ;
            }
":"         {   if(E2T_Debug_Lex)   printf("Recognized Operator COLON, lineno is %d\n", e2t_yylineno);
                return COLON;
            }

    /*标识符*/
{var_T}    {    if(E2T_Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", e2t_yytext, e2t_yylineno);
                e2t_yylval.kToken = new E2T_Token (SYMBOL, e2t_yytext, e2t_yylineno);
                return SYMBOL;
            }

{var_t}    {    if(E2T_Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", e2t_yytext, e2t_yylineno);
                e2t_yylval.kToken = new E2T_Token (SYMBOL, e2t_yytext, e2t_yylineno);
                return SYMBOL;
            }

{var_p}    {    if(E2T_Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", e2t_yytext, e2t_yylineno);
                e2t_yylval.kToken = new E2T_Token (SYMBOL, e2t_yytext, e2t_yylineno);
                return SYMBOL;
            }

    /*常量*/
{number}|-{number}    {   int num = int(strtol(e2t_yytext, nullptr, 10));
                if(E2T_Debug_Lex)   printf("Recognized Literal %d, lineno is %d\n", num, e2t_yylineno);
                e2t_yylval.kToken = new E2T_Token (NUM, num, e2t_yylineno);
                return NUM;
            }


"//".*$     {  if(E2T_Debug_Lex)    printf("Comments, Ignored!\n");}
"/*"[^"*"]*(\*+[^"*/"][^"*"]*)*\*+"/"  { if(E2T_Debug_Lex)    printf("Comments, Ignored!\n");}

    /*其它情况直接返回*/
.           {   if(E2T_Debug_Lex)    printf("Other Cases: %s, lineno is %d\n", e2t_yytext, e2t_yylineno);
                return e2t_yytext[0];
            }

%%

int e2t_yywrap(void){
    return 1;
}
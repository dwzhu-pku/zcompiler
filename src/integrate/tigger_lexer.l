%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"tigger_ast.hpp"
    #include"tigger_parser.tab.hpp"
%}
%option yylineno
%option prefix="t2r_yy"

digit_10   [0-9]
var   v[0-9]+
reg   x0|s[0-9]|s10|s11|t[0-6]|a[0-7]
letter  [a-zA-Z_]
fname    f_({letter}|{digit_10})*
label    l{digit_10}+
number  {digit_10}+ 

%%
[ \r\n\t]   {   if(T2R_Debug_Lex)   printf("Whitespace, Ignored!, lineno is %d\n", t2r_yylineno);}

    /*全局声明关键字*/
malloc      {   if(T2R_Debug_Lex)   printf("Recognized type keyword malloc, lineno is %d\n", t2r_yylineno);
                return MALLOC;
            }

    /*控制流关键字*/
if      {   if(T2R_Debug_Lex)   printf("Recognized control flow keyword IF, lineno is %d\n", t2r_yylineno);
            return IF;
        }

goto    {   if(T2R_Debug_Lex)   printf("Recognized control flow keyword GOTO, lineno is %d\n", t2r_yylineno);
            return GOTO;
        }

{label}     {   if(T2R_Debug_Lex)   printf("Recognized control flow keyword LABEL, lineno is %d\n", t2r_yylineno);
                t2r_yylval.kToken = new Token(LABEL, t2r_yytext, t2r_yylineno);
                return LABEL;
            }

return      {   if(T2R_Debug_Lex)   printf("Recognized control flow keyword RETURN, lineno is %d\n", t2r_yylineno);
                return RETURN;
            }

    /*函数关键字*/
{fname}     {   if(T2R_Debug_Lex)   printf("Recognized function name, lineno is %d\n", t2r_yylineno);
                t2r_yylval.kToken = new Token(FNAME, t2r_yytext, t2r_yylineno);
                return FNAME;
            }

call    {   if(T2R_Debug_Lex)   printf("Recognized function call, lineno is %d\n", t2r_yylineno);
            return CALL;
        }

end     {   if(T2R_Debug_Lex)   printf("Recognized function end, lineno is %d\n", t2r_yylineno);
            return END;
        }

    /*其它指令*/
loadaddr        {   if(T2R_Debug_Lex)   printf("Recognized instruction loadaddr, lineno is %d\n", t2r_yylineno);
                    return LOADADDR;
                }

load        {   if(T2R_Debug_Lex)   printf("Recognized instruction load, lineno is %d\n", t2r_yylineno);
                return LOAD;
            }

store           {   if(T2R_Debug_Lex)   printf("Recognized instruction store, lineno is %d\n", t2r_yylineno);
                    return STORE;
                }  

    /*运算符*/

"+"|"-"|"*"|"/"|"%"|"!"|"&&"|"||"|"<"|"<="|">"|">="|"=="|"!="     {
            if(T2R_Debug_Lex)   printf("Recognized Operator %s, lineno is %d\n", t2r_yytext, t2r_yylineno);
            t2r_yylval.kToken = new Token(Op, t2r_yytext, t2r_yylineno);
            return Op;
        }


"="         {   if(T2R_Debug_Lex)   printf("Recognized Operator ASSIGN, lineno is %d\n", t2r_yylineno);
                return ASSIGN;
            }

    /*标点符号*/

"["         {   if(T2R_Debug_Lex)   printf("Recognized Operator LKHZ, lineno is %d\n", t2r_yylineno);
                return LKHZ;
            }
"]"         {   if(T2R_Debug_Lex)   printf("Recognized Operator RKHZ, lineno is %d\n", t2r_yylineno);
                return RKHZ;
            }
":"         {   if(T2R_Debug_Lex)   printf("Recognized Operator COLON, lineno is %d\n", t2r_yylineno);
                return COLON;
            }

    /*标识符*/

{var}       {   if(T2R_Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", t2r_yytext, t2r_yylineno);
                t2r_yylval.kToken = new Token(VAR, t2r_yytext, t2r_yylineno);
                return VAR;
            }

{reg}       {   if(T2R_Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", t2r_yytext, t2r_yylineno);
                t2r_yylval.kToken = new Token(REG, t2r_yytext, t2r_yylineno);
                return REG;
            }

    /*常量*/
{number}|-{number}      {   int num = int(strtol(t2r_yytext, nullptr, 10));
                            if(T2R_Debug_Lex)   printf("Recognized number %d, lineno is %d\n", num, t2r_yylineno);
                            t2r_yylval.kToken = new Token(NUM, num, t2r_yylineno);
                            return NUM;
                        }


"//".*$     {  if(T2R_Debug_Lex)    printf("Comments, Ignored!\n");}
"/*"[^"*"]*(\*+[^"*/"][^"*"]*)*\*+"/"  { if(T2R_Debug_Lex)    printf("Comments, Ignored!\n");}

    /*其它情况直接返回*/
.           {   if(T2R_Debug_Lex)    printf("Other Cases: %s, lineno is %d\n", t2r_yytext, t2r_yylineno);
                return t2r_yytext[0];
            }

%%

int t2r_yywrap(void){
    return 1;
}
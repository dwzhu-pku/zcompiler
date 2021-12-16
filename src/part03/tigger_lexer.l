%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"tigger_ast.hpp"
    #include"tigger_parser.tab.hpp"
%}
%option yylineno

digit_10   [0-9]
var   v[0-9]+
reg   x0|s[0-9]|s10|s11|t[0-6]|a[0-7]
letter  [a-zA-Z_]
fname    f_({letter}|{digit_10})*
label    l{digit_10}+
number  {digit_10}+ 

%%
[ \r\n\t]   {   if(Debug_Lex)   printf("Whitespace, Ignored!, lineno is %d\n", yylineno);}

    /*全局声明关键字*/
malloc      {   if(Debug_Lex)   printf("Recognized type keyword malloc, lineno is %d\n", yylineno);
                return MALLOC;
            }

    /*控制流关键字*/
if      {   if(Debug_Lex)   printf("Recognized control flow keyword IF, lineno is %d\n", yylineno);
            return IF;
        }

goto    {   if(Debug_Lex)   printf("Recognized control flow keyword GOTO, lineno is %d\n", yylineno);
            return GOTO;
        }

{label}     {   if(Debug_Lex)   printf("Recognized control flow keyword LABEL, lineno is %d\n", yylineno);
                yylval.kToken = new Token(LABEL, yytext, yylineno);
                return LABEL;
            }

return      {   if(Debug_Lex)   printf("Recognized control flow keyword RETURN, lineno is %d\n", yylineno);
                return RETURN;
            }

    /*函数关键字*/
{fname}     {   if(Debug_Lex)   printf("Recognized function name, lineno is %d\n", yylineno);
                yylval.kToken = new Token(FNAME, yytext, yylineno);
                return FNAME;
            }

call    {   if(Debug_Lex)   printf("Recognized function call, lineno is %d\n", yylineno);
            return CALL;
        }

end     {   if(Debug_Lex)   printf("Recognized function end, lineno is %d\n", yylineno);
            return END;
        }

    /*其它指令*/
loadaddr        {   if(Debug_Lex)   printf("Recognized instruction loadaddr, lineno is %d\n", yylineno);
                    return LOADADDR;
                }

load        {   if(Debug_Lex)   printf("Recognized instruction load, lineno is %d\n", yylineno);
                return LOAD;
            }

store           {   if(Debug_Lex)   printf("Recognized instruction store, lineno is %d\n", yylineno);
                    return STORE;
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

{var}       {   if(Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", yytext, yylineno);
                yylval.kToken = new Token(VAR, yytext, yylineno);
                return VAR;
            }

{reg}       {   if(Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", yytext, yylineno);
                yylval.kToken = new Token(REG, yytext, yylineno);
                return REG;
            }

    /*常量*/
{number}|-{number}      {   int num = int(strtol(yytext, nullptr, 10));
                            if(Debug_Lex)   printf("Recognized number %d, lineno is %d\n", num, yylineno);
                            yylval.kToken = new Token(NUM, num, yylineno);
                            return NUM;
                        }


"//".*$     {  if(Debug_Lex)    printf("Comments, Ignored!\n");}
"/*"[^"*"]*(\*+[^"*/"][^"*"]*)*\*+"/"  { if(Debug_Lex)    printf("Comments, Ignored!\n");}

    /*其它情况直接返回*/
.           {   if(Debug_Lex)    printf("Other Cases: %s, lineno is %d\n", yytext, yylineno);
                return yytext[0];
            }

%%

int yywrap(void){
    return 1;
}
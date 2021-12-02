%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"ast.hpp"
    #include"parser.tab.hpp"
%}
%option yylineno

digit_10   [0-9]
digit_8   [0-7]
digit_16   [0-9A-Fa-f]
letter  [a-zA-Z_]
identity    {letter}({letter}|{digit_10})*
number_10  [1-9]{digit_10}* 
number_8  0{digit_8}* 
number_16  (0x|0X){digit_16}* 

%%
[ \r\n\t]   {   if(Debug_Lex)   printf("Whitespace, Ignored!, lineno is %d\n", yylineno);}

    /*类型关键字*/
int     {   if(Debug_Lex)   printf("Recognized type keyword INT, lineno is %d\n", yylineno);
            return INT;
        }
void    {   if(Debug_Lex)   printf("Recognized type keyword VOID, lineno is %d\n", yylineno);
            return VOID;
        }
const   {   if(Debug_Lex)   printf("Recognized type keyword CONST, lineno is %d\n", yylineno);
            return CONST;
        }

    /*控制流关键字*/
if      {   if(Debug_Lex)   printf("Recognized control flow keyword IF, lineno is %d\n", yylineno);
            return IF;
        }
else    {   if(Debug_Lex)   printf("Recognized control flow keyword ELSE, lineno is %d\n", yylineno);
            return ELSE;
        }
while   {   if(Debug_Lex)   printf("Recognized control flow keyword WHILE, lineno is %d\n", yylineno);
            return WHILE;
        }
break   {   if(Debug_Lex)   printf("Recognized control flow keyword BREAK, lineno is %d\n", yylineno);
            return BREAK;
        }
continue    {   if(Debug_Lex)   printf("Recognized control flow keyword CONTINUE, lineno is %d\n", yylineno);
                return CONTINUE;
            }
return      {   if(Debug_Lex)   printf("Recognized control flow keyword RETURN, lineno is %d\n", yylineno);
                return RETURN;
            }

    /*运算符*/

"+"         {   if(Debug_Lex)   printf("Recognized Operator ADD, lineno is %d\n", yylineno);
                return ADD;
            }
"-"         {   if(Debug_Lex)   printf("Recognized Operator SUB, lineno is %d\n", yylineno);
                return SUB;
            }
"*"         {   if(Debug_Lex)   printf("Recognized Operator MUL, lineno is %d\n", yylineno);
                return MUL;
            }
"/"         {   if(Debug_Lex)   printf("Recognized Operator DIV, lineno is %d\n", yylineno);
                return DIV;
            }
"%"         {   if(Debug_Lex)   printf("Recognized Operator MOD, lineno is %d\n", yylineno);
                return MOD;
            }
"!"         {   if(Debug_Lex)   printf("Recognized Operator NOT, lineno is %d\n", yylineno);
                return NOT;
            }

"<"         {   if(Debug_Lex)   printf("Recognized Operator LT, lineno is %d\n", yylineno);
                return LT;
            }
">"         {   if(Debug_Lex)   printf("Recognized Operator GT, lineno is %d\n", yylineno);
                return GT;
            }
"<="        {   if(Debug_Lex)   printf("Recognized Operator LE, lineno is %d\n", yylineno);
                return LE;
            }
">="        {   if(Debug_Lex)   printf("Recognized Operator GE, lineno is %d\n", yylineno);
                return GE;
            }
"=="        {   if(Debug_Lex)   printf("Recognized Operator EQ, lineno is %d\n", yylineno);
                return EQ;
            }
"!="        {   if(Debug_Lex)   printf("Recognized Operator NE, lineno is %d\n", yylineno);
                return NE;
            }

"&&"        {   if(Debug_Lex)   printf("Recognized Operator LAND, lineno is %d\n", yylineno);
                return LAND;
            }
"||"        {   if(Debug_Lex)   printf("Recognized Operator LOR, lineno is %d\n", yylineno);
                return LOR;
            }

"="         {   if(Debug_Lex)   printf("Recognized Operator ASSIGN, lineno is %d\n", yylineno);
                return ASSIGN;
            }

    /*标点符号*/

";"         {   if(Debug_Lex)   printf("Recognized Operator SEMI, lineno is %d\n", yylineno);
                return SEMI;
            }
","         {   if(Debug_Lex)   printf("Recognized Operator COMMA, lineno is %d\n", yylineno);
                return COMMA;
            }
"("         {   if(Debug_Lex)   printf("Recognized Operator LKHX, lineno is %d\n", yylineno);
                return LKHX;
            }
")"         {   if(Debug_Lex)   printf("Recognized Operator RKHX, lineno is %d\n", yylineno);
                return RKHX;
            }
"["         {   if(Debug_Lex)   printf("Recognized Operator LKHZ, lineno is %d\n", yylineno);
                return LKHZ;
            }
"]"         {   if(Debug_Lex)   printf("Recognized Operator RKHZ, lineno is %d\n", yylineno);
                return RKHZ;
            }
"{"         {   if(Debug_Lex)   printf("Recognized Operator LKHD, lineno is %d\n", yylineno);
                return LKHD;
            }
"}"         {   if(Debug_Lex)   printf("Recognized Operator RKHD, lineno is %d\n", yylineno);
                return RKHD;
            }

    /*标识符*/
{identity}  {
                if(Debug_Lex)   printf("Recognized Identity %s, lineno is %d\n", yytext, yylineno) ;
                yylval.kToken = new Token(IDENT, yytext, yylineno);
                return IDENT;
            }

    /*常量*/
{number_10}    {
                int num = int(strtol(yytext, nullptr, 10));
                if(Debug_Lex)   printf("Recognized Literal %d, lineno is %d\n", num, yylineno);
                yylval.kToken = new Token (VAL_CONST, num, yylineno);
                return VAL_CONST;
            }

{number_8}    {
                int num = int(strtol(yytext, nullptr, 8));
                if(Debug_Lex)   printf("Recognized Literal %d, lineno is %d\n", num, yylineno);
                yylval.kToken = new Token (VAL_CONST, num, yylineno);
                return VAL_CONST;
            }

{number_16}    {
                int num = int(strtol(yytext, nullptr, 16));
                if(Debug_Lex)   printf("Recognized Literal %d, lineno is %d\n", num, yylineno);
                yylval.kToken = new Token (VAL_CONST, num, yylineno);
                return VAL_CONST;
            }

"//".*$     {  if(Debug_Lex)    printf("Comments, Ignored!");}
"/*"[^"*"]*(\*+[^"*/"][^"*"]*)*\*+"/"  { if(Debug_Lex)    printf("Comments, Ignored!");}

    /*其它情况直接返回*/
.           {
                if(Debug_Lex)    printf("Other Cases: %s, lineno is %d\n", yytext, yylineno);
                return yytext[0];
            }

%%

int yywrap(void){
    return 1;
}
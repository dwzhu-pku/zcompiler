%{
    #include<stdio.h>
    #include<stdlib.h>
    #include"ast.hpp"
    #include"parser.tab.hpp"
%}

digit_10   [0-9]
digit_8   [0-7]
digit_16   [0-9A-Fa-f]
letter  [a-zA-Z_]
identity    {letter}({letter}|{digit_10})*
number_10  [1-9]{digit_10}* 
number_8  0{digit_8}* 
number_16  (0x|0X){digit_16}* 

%%
[ \r\n\t]   {   if(Debug_Lex)   printf("Whitespace, Ignored!\n");}

    /*类型关键字*/
int     {   if(Debug_Lex)   printf("Recognized type keyword INT\n");
            return INT;
        }
void    {   if(Debug_Lex)   printf("Recognized type keyword VOID\n");
            return VOID;
        }
const   {   if(Debug_Lex)   printf("Recognized type keyword CONST\n");
            return CONST;
        }

    /*控制流关键字*/
if      {   if(Debug_Lex)   printf("Recognized control flow keyword IF\n");
            return IF;
        }
else    {   if(Debug_Lex)   printf("Recognized control flow keyword ELSE\n");
            return ELSE;
        }
while   {   if(Debug_Lex)   printf("Recognized control flow keyword WHILE\n");
            return WHILE;
        }
break   {   if(Debug_Lex)   printf("Recognized control flow keyword BREAK\n");
            return BREAK;
        }
continue    {   if(Debug_Lex)   printf("Recognized control flow keyword CONTINUE\n");
                return CONTINUE;
            }
return      {   if(Debug_Lex)   printf("Recognized control flow keyword RETURN\n");
                return RETURN;
            }

    /*运算符*/

"+"         {   if(Debug_Lex)   printf("Recognized Operator ADD\n");
                return ADD;
            }
"-"         {   if(Debug_Lex)   printf("Recognized Operator SUB\n");
                return SUB;
            }
"*"         {   if(Debug_Lex)   printf("Recognized Operator MUL\n");
                return MUL;
            }
"/"         {   if(Debug_Lex)   printf("Recognized Operator DIV\n");
                return DIV;
            }
"%"         {   if(Debug_Lex)   printf("Recognized Operator MOD\n");
                return MOD;
            }
"!"         {   if(Debug_Lex)   printf("Recognized Operator NOT\n");
                return NOT;
            }

"<"         {   if(Debug_Lex)   printf("Recognized Operator LT\n");
                return LT;
            }
">"         {   if(Debug_Lex)   printf("Recognized Operator GT\n");
                return GT;
            }
"<="        {   if(Debug_Lex)   printf("Recognized Operator LE\n");
                return LE;
            }
">="        {   if(Debug_Lex)   printf("Recognized Operator GE\n");
                return GE;
            }
"=="        {   if(Debug_Lex)   printf("Recognized Operator EQ\n");
                return EQ;
            }
"!="        {   if(Debug_Lex)   printf("Recognized Operator NE\n");
                return NE;
            }

"&&"        {   if(Debug_Lex)   printf("Recognized Operator LAND\n");
                return LAND;
            }
"||"        {   if(Debug_Lex)   printf("Recognized Operator LOR\n");
                return LOR;
            }

"="         {   if(Debug_Lex)   printf("Recognized Operator ASSIGN\n");
                return ASSIGN;
            }

    /*标点符号*/

";"         {   if(Debug_Lex)   printf("Recognized Operator SEMI\n");
                return SEMI;
            }
","         {   if(Debug_Lex)   printf("Recognized Operator COMMA\n");
                return COMMA;
            }
"("         {   if(Debug_Lex)   printf("Recognized Operator LKHX\n");
                return LKHX;
            }
")"         {   if(Debug_Lex)   printf("Recognized Operator RKHX\n");
                return RKHX;
            }
"["         {   if(Debug_Lex)   printf("Recognized Operator LKHZ\n");
                return LKHZ;
            }
"]"         {   if(Debug_Lex)   printf("Recognized Operator RKHZ\n");
                return RKHZ;
            }
"{"         {   if(Debug_Lex)   printf("Recognized Operator LKHD\n");
                return LKHD;
            }
"}"         {   if(Debug_Lex)   printf("Recognized Operator RKHD\n");
                return RKHD;
            }

    /*标识符*/
{identity}  {
                if(Debug_Lex)   printf("Recognized Identity %s\n", yytext) ;
                yylval.kToken = new Token(IDENT, yytext, yylineno);
                return IDENT;
            }

    /*常量*/
{number_10}    {
                int num = int(strtol(yytext, nullptr, 10));
                if(Debug_Lex)   printf("Recognized Literal %d\n",num);
                yylval.kToken = new Token (VAL_CONST, num, yylineno);
                return VAL_CONST;
            }

{number_8}    {
                int num = int(strtol(yytext, nullptr, 8));
                if(Debug_Lex)   printf("Recognized Literal %d\n",num);
                yylval.kToken = new Token (VAL_CONST, num, yylineno);
                return VAL_CONST;
            }

{number_16}    {
                int num = int(strtol(yytext, nullptr, 16));
                if(Debug_Lex)   printf("Recognized Literal %d\n",num);
                yylval.kToken = new Token (VAL_CONST, num, yylineno);
                return VAL_CONST;
            }

"//".*$     {  if(Debug_Lex)    printf("Comments, Ignored!");}
"/*"[^"*"]*(\*+[^"*/"][^"*"]*)*\*+"/"  { if(Debug_Lex)    printf("Comments, Ignored!");}

    /*其它情况直接返回*/
.           {
                if(Debug_Lex)    printf("Other Cases: %s\n", yytext);
                return yytext[0];
            }

%%

int yywrap(void){
    return 1;
}
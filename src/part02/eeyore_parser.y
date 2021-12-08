%{
    #include<stdio.h>
    #include"eeyore_ast.hpp"
    extern int yylex();
    extern int yylineno;
    extern FILE * yyin;
    extern FILE * yyout;
    void yyerror(BaseAst**, const char *);
%}

%union{
    Token* kToken;
    BaseAst* kPtrAst;
};
%parse-param {BaseAst* *root}

%token <kToken> VAR // 类型关键字
%token <kToken> IF GOTO LABEL RETURN // 控制流关键字
%token <kToken> FNAME CALL PARAM END // 函数关键字
%token <kToken> Op ASSIGN// 运算符 赋值运算
%token <kToken> NUM SYMBOL// 常量值
%token <kToken> COLON LKHZ RKHZ   // 标点符号(: [ ])

%type <kPtrAst> Program Declaration Initialization FunctionDef 
%type <kPtrAst> FunctionHeader FunctionEnd
%type <kPtrAst> Statements Statement Expression RightValue 

%%
Program        : Declaration Program
                    {
                        
                    }
                | Initialization  Program
                    {
                        
                    }
                | FunctionDef  Program
                    {
                        
                    }
                |
                    {

                    }
                ;

Declaration     : VAR SYMBOL
                    {

                    }
                | VAR NUM SYMBOL
                    {

                    }
                ;

Initialization  : SYMBOL ASSIGN NUM
                    {

                    }
                | SYMBOL LKHZ NUM RKHZ ASSIGN NUM
                    {

                    }
                ;

FunctionDef     : FunctionHeader Statements FunctionEnd
                    {

                    }
                ;

FunctionHeader  : FNAME LKHZ NUM RKHZ
                    {

                    }
                ;

Statements      : Statement Statements
                    {

                    }
                |
                    {
                        
                    }
                ;

FunctionEnd     : END FNAME
                    {

                    }
                ;

Statement       : Expression
                    {

                    }
                | Declaration
                    {

                    }
                ;

Expression      : SYMBOL ASSIGN RightValue Op RightValue
                    {

                    }
                | SYMBOL ASSIGN Op RightValue
                    {

                    }
                | SYMBOL ASSIGN RightValue
                    {

                    }
                | SYMBOL LKHZ RightValue RKHZ ASSIGN RightValue
                    {

                    }
                | SYMBOL ASSIGN SYMBOL LKHZ RightValue RKHZ
                    {

                    }
                | IF RightValue Op RightValue GOTO LABEL
                    {

                    }
                | GOTO LABEL
                    {

                    }
                | LABEL COLON
                    {

                    }
                | PARAM RightValue
                    {

                    }
                | CALL FNAME
                    {

                    }
                | SYMBOL ASSIGN CALL FNAME
                    {

                    }
                | RETURN RightValue
                    {

                    }
                | RETURN
                    {

                    }
                ;


RightValue      : SYMBOL
                    {

                    }
                | NUM
                    {

                    }
                ;

%%

void yyerror(BaseAst**, const char *){
    printf("Syntax error at line %d. \n", yylineno);
};

int yywrap(void){
    return 1;
}
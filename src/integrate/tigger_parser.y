%{
    #include<stdio.h>
    #include"tigger_ast.hpp"
    extern int t2r_yylex();
    extern int t2r_yylineno;
    extern FILE * t2r_yyin;
    extern FILE * t2r_yyout;
    void t2r_yyerror(const char *s);

    void genBinOp(string reg1, string reg2, string reg3, string op){
        if (op == "+"){
            t2r_code_list.push_back("add "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "-"){
            t2r_code_list.push_back("sub "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "*"){
            t2r_code_list.push_back("mul "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "/"){
            t2r_code_list.push_back("div "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "%"){
            t2r_code_list.push_back("rem "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "<"){
            t2r_code_list.push_back("slt "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == ">"){
            t2r_code_list.push_back("sgt "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "<="){
            t2r_code_list.push_back("sgt "+ reg1 + ", " + reg2 + ", " + reg3);
            t2r_code_list.push_back("seqz " + reg1 + ", " + reg1);
        } else if (op == ">="){
            t2r_code_list.push_back("slt "+ reg1 + ", " + reg2 + ", " + reg3);
            t2r_code_list.push_back("seqz " + reg1 + ", " + reg1);
        } else if (op == "&&"){
            t2r_code_list.push_back("snez "+ reg1 + ", " + reg2);
            t2r_code_list.push_back("snez s0, " + reg3);
            t2r_code_list.push_back("and "+ reg1 + ", " + reg1 + ", s0");
        } else if (op == "||"){
            t2r_code_list.push_back("or "+ reg1 + ", " + reg2 + ", " + reg3);
            t2r_code_list.push_back("snez "+ reg1 + ", " + reg1);
        } else if (op == "!="){
            t2r_code_list.push_back("xor "+ reg1 + ", " + reg2 + ", " + reg3);
            t2r_code_list.push_back("snez "+ reg1 + ", " + reg1);
        } else if (op == "=="){
            t2r_code_list.push_back("xor "+ reg1 + ", " + reg2 + ", " + reg3);
            t2r_code_list.push_back("seqz "+ reg1 + ", " + reg1);
        } else{
            printf("Error! Unexpected case\n");
            exit(-1);
        }
    }

    int stk = 0;
%}
%define api.prefix {t2r_yy}
%union{
    Token* kToken;
};

%token <kToken> VAR REG// 全局变量 寄存器
%token <kToken> IF GOTO LABEL RETURN // 控制流
%token <kToken> FNAME CALL END // 函数
%token <kToken> Op ASSIGN// 运算符
%token <kToken> NUM // 数字 
%token <kToken> COLON LKHZ RKHZ   // 标点符号
%token <kToken> MALLOC LOAD LOADADDR STORE  // 其它指令

%type <kToken> Program GlobalVarDecl FunctionDef FunctionHeader Expressions FunctionEnd Expression

%%
Program         : GlobalVarDecl
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Program\n");
                    }
                | FunctionDef
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Program\n");
                    }
                | Program GlobalVarDecl
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Program\n");
                    }
                | Program FunctionDef
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Program\n");
                    }
                ;

GlobalVarDecl   : VAR ASSIGN NUM
                    {
                        if (T2R_Debug_Parser)   printf("Trace: GlobalVarDecl\n");
                        string var_name = ($1)->name;
                        int num = ($3)->val;
                        t2r_code_list.push_back("\t.global\t" + var_name);
                        t2r_code_list.push_back("\t.section\t.sdata");
                        t2r_code_list.push_back("\t.align\t2");
                        t2r_code_list.push_back("\t.type\t" + var_name + ", @object");
                        t2r_code_list.push_back("\t.size\t" + var_name + ", 4");
                        t2r_code_list.push_back(var_name + ":");
                        t2r_code_list.push_back("\t.word\t" + to_string(num));
                    }
                | VAR ASSIGN MALLOC NUM
                    {
                        if (T2R_Debug_Parser)   printf("Trace: GlobalVarDecl\n");
                        string var_name = ($1)->name;
                        int num = ($4)->val;
                        t2r_code_list.push_back("\t.comm\t" + var_name + ", " + to_string(num) + ", 4");
                    }
                ;

FunctionDef     : FunctionHeader FunctionEnd
                    {
                        if (T2R_Debug_Parser)   printf("Trace: FunctionDef\n");
                    }
                | FunctionHeader Expressions FunctionEnd
                    {
                        if (T2R_Debug_Parser)   printf("Trace: FunctionDef\n");
                    }
                ;

FunctionHeader  : FNAME LKHZ NUM RKHZ LKHZ NUM RKHZ
                    {
                        if (T2R_Debug_Parser)   printf("Trace: FunctionHeader\n");
                        string func_name = (($1)->name).substr(2);
                        t2r_code_list.push_back("\t.text");
                        t2r_code_list.push_back("\t.align\t2");
                        t2r_code_list.push_back("\t.global\t" + func_name);
                        t2r_code_list.push_back("\t.type\t" + func_name + ", @function");
                        t2r_code_list.push_back(func_name + ":");
                        stk = ((($6)->val)/4 + 1) * 16;

                        if (-stk >= -2048 && -stk <= 2047){
                            t2r_code_list.push_back("\taddi\tsp, sp, -" + to_string(stk));
                            t2r_code_list.push_back("\tsw\tra, " + to_string(stk-4) + "(sp)");
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(-stk));
                            t2r_code_list.push_back("add sp, sp, s0");
                            t2r_code_list.push_back("li s0, " + to_string(stk-4));
                            t2r_code_list.push_back("add s0, sp, s0");
                            t2r_code_list.push_back("\tsw\tra, 0(s0)");
                        }

                    }
                ;

Expressions     : Expression
                | Expressions Expression
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expressions\n");
                    }
                ;

FunctionEnd     : END FNAME
                    {
                        if (T2R_Debug_Parser)   printf("Trace: FunctionEnd\n");
                        string func_name = (($2)->name).substr(2);
                        t2r_code_list.push_back("\t.size\t" + func_name + ", .-" + func_name);
                    }
                ;

Expression      : REG ASSIGN REG Op REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string reg1 = ($1)->name;
                        string reg2 = ($3)->name;
                        string reg3 = ($5)->name;
                        string op = ($4)->name;
                        genBinOp(reg1, reg2, reg3, op);
                    }
                | REG ASSIGN REG Op NUM
                    {
                        // 需要分类讨论num的大小，以此使用不同的指令
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        int num = ($5)->val;
                        string op = ($4)->name;
                        if (num >= -2048 && num <= 2047 && op == "+"){
                            t2r_code_list.push_back("addi "+ ($1)->name + ", " + ($3)->name + ", " + to_string(num));
                        } else if (num >= -2048 && num <= 2047 && op == "-"){
                            t2r_code_list.push_back("addi "+ ($1)->name + ", " + ($3)->name + ", " + to_string(-num));
                        } else if (num >= -2048 && num <= 2047 && op == "<"){
                            t2r_code_list.push_back("slti "+ ($1)->name + ", " + ($3)->name + ", " + to_string(num));
                        } else if (num >= -2048 && num <= 2047 && op == "||"){
                            t2r_code_list.push_back("ori "+ ($1)->name + ", " + ($3)->name + ", " + to_string(num));
                            t2r_code_list.push_back("snez "+ ($1)->name + ", " + ($1)->name);
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(num));
                            genBinOp(($1)->name, ($3)->name, "s0", op);
                        }
                    }
                | REG ASSIGN Op REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string reg1 = ($1)->name;
                        string reg2 = ($4)->name;
                        string op = ($3)->name;
                        if (op == "-"){
                            t2r_code_list.push_back("neg " + reg1 + ", " + reg2);
                        } else if (op == "!"){
                            t2r_code_list.push_back("seqz " + reg1 + ", " + reg2);
                        } else{
                            printf("Error! Unexpected Operator!\n");
                            t2r_code_list.push_back("-----");
                            exit(-1);
                        }
                    }
                | REG ASSIGN REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        t2r_code_list.push_back("mv " + ($1)->name + ", " + ($3)->name);
                    }
                | REG ASSIGN NUM
                    {   
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        t2r_code_list.push_back("li " + ($1)->name + ", " + to_string(($3)->val));
                    }
                | REG LKHZ NUM RKHZ ASSIGN REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        int num = ($3)->val;

                        if (num >= -2048 && num <= 2047){
                            t2r_code_list.push_back("sw " + ($6)->name + ", " + to_string(num) + "(" + ($1)->name + ")");
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(num));
                            t2r_code_list.push_back("add s0, s0, " + ($1)->name);
                            t2r_code_list.push_back("sw " + ($6)->name + ", 0(s0)");
                        }

                    }
                | REG ASSIGN REG LKHZ NUM RKHZ
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        int num = ($5)->val;
                        if (num >= -2048 && num <= 2047){
                            t2r_code_list.push_back("lw " + ($1)->name + ", " + to_string(num) + "(" + ($3)->name + ")");
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(num));
                            t2r_code_list.push_back("add s0, s0, " + ($3)->name);
                            t2r_code_list.push_back("lw " + ($1)->name + ", 0(s0)");
                        }
                    }
                | IF REG Op REG GOTO LABEL
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string reg1 = ($2)->name;
                        string reg2 = ($4)->name;
                        string label = "." + ($6)->name;
                        string op = ($3)->name;
                        if (op == "<"){
                            t2r_code_list.push_back("blt " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == ">"){
                            t2r_code_list.push_back("bgt " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == "<="){
                            t2r_code_list.push_back("ble " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == ">="){
                            t2r_code_list.push_back("bge " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == "!="){
                            t2r_code_list.push_back("bne " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == "=="){
                            t2r_code_list.push_back("beq " + reg1 + ", " + reg2 + ", " + label);
                        } else {
                            printf("Error! Unexpected Operator!\n");
                            exit(-1);
                        }
                    }
                | GOTO LABEL
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string label = "." + ($2)->name;
                        t2r_code_list.push_back("j " + label);
                    }
                | LABEL COLON
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string label = "." + ($1)->name;
                        t2r_code_list.push_back(label + ":");
                    }
                | CALL FNAME
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string func_name = (($2)->name).substr(2);
                        t2r_code_list.push_back("call " + func_name);
                    }
                | RETURN
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");

                        if (stk >= -2048 && stk <= 2047){
                            t2r_code_list.push_back("\tlw\tra, " + to_string(stk-4) + "(sp)");
                            t2r_code_list.push_back("\taddi\tsp, sp, " + to_string(stk));
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(stk-4));
                            t2r_code_list.push_back("add s0, sp, s0");
                            t2r_code_list.push_back("\tlw\tra, 0(s0)");
                            t2r_code_list.push_back("li s0, " + to_string(stk));
                            t2r_code_list.push_back("add sp, sp, s0");
                        }
                        t2r_code_list.push_back("ret");
                    }
                | STORE REG NUM
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        int num = 4 * ($3)->val;

                        if (num >= -2048 && num <= 2047){
                            t2r_code_list.push_back("sw " + ($2)->name + ", " + to_string(num) + "(sp)");
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(num));
                            t2r_code_list.push_back("add s0, sp, s0");
                            t2r_code_list.push_back("sw " + ($2)->name + ", 0(s0)");
                        }

                    }
                | LOAD NUM REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        int num = 4 * ($2)->val;

                        if (num >= -2048 && num <= 2047){
                            t2r_code_list.push_back("lw " + ($3)->name + ", " + to_string(num) + "(sp)");
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(num));
                            t2r_code_list.push_back("add s0, sp, s0");
                            t2r_code_list.push_back("lw " + ($3)->name + ", 0(s0)");
                        }

                    }
                | LOAD VAR REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        string var_name = ($2)->name;
                        string reg = ($3)->name;
                        t2r_code_list.push_back("lui " + reg + ", %hi(" + var_name + ")");
                        t2r_code_list.push_back("lw " + reg + ", %lo(" + var_name + ")(" + reg + ")");
                    }
                | LOADADDR NUM REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        int num = 4 * ($2)->val;
                        string reg = ($3)->name;
                        if (num >= -2048 && num <= 2047){
                            t2r_code_list.push_back("addi " + reg + ", sp, " + to_string(num));
                        } else{
                            t2r_code_list.push_back("li s0, " + to_string(num));
                            t2r_code_list.push_back("add " + reg + ", sp, s0");
                        }
                    }
                | LOADADDR VAR REG
                    {
                        if (T2R_Debug_Parser)   printf("Trace: Expression\n");
                        t2r_code_list.push_back("la " + ($3)->name + ", " + ($2)->name);
                    }
                ;


%%

void t2r_yyerror(const char *s){
    printf("Tigger Syntax error at line %d, error is %s. \n", t2r_yylineno, s);
};

int t2r_yywrap(void){
    return 1;
}
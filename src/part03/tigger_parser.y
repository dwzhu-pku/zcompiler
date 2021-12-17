%{
    #include<stdio.h>
    #include"tigger_ast.hpp"
    extern int yylex();
    extern int yylineno;
    extern FILE * yyin;
    extern FILE * yyout;
    void yyerror(const char *);

    vector<string>code_list;

    void genBinOp(string reg1, string reg2, string reg3, string op){
        if (op == "+"){
            code_list.push_back("add "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "-"){
            code_list.push_back("sub "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "*"){
            code_list.push_back("mul "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "/"){
            code_list.push_back("div "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "%"){
            code_list.push_back("rem "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "<"){
            code_list.push_back("slt "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == ">"){
            code_list.push_back("sgt "+ reg1 + ", " + reg2 + ", " + reg3);
        } else if (op == "<="){
            code_list.push_back("sgt "+ reg1 + ", " + reg2 + ", " + reg3);
            code_list.push_back("seqz " + reg1 + ", " + reg1);
        } else if (op == ">="){
            code_list.push_back("slt "+ reg1 + ", " + reg2 + ", " + reg3);
            code_list.push_back("seqz " + reg1 + ", " + reg1);
        } else if (op == "&&"){
            code_list.push_back("snez "+ reg1 + ", " + reg2);
            code_list.push_back("snez s0, " + reg3);
            code_list.push_back("and "+ reg1 + ", " + reg1 + ", s0");
        } else if (op == "||"){
            code_list.push_back("or "+ reg1 + ", " + reg2 + ", " + reg3);
            code_list.push_back("snez "+ reg1 + ", " + reg1);
        } else if (op == "!="){
            code_list.push_back("xor "+ reg1 + ", " + reg2 + ", " + reg3);
            code_list.push_back("snez "+ reg1 + ", " + reg1);
        } else if (op == "=="){
            code_list.push_back("xor "+ reg1 + ", " + reg2 + ", " + reg3);
            code_list.push_back("seqz "+ reg1 + ", " + reg1);
        } else{
            printf("Error! Unexpected case\n");
            exit(-1);
        }
    }

    int stk = 0;
%}

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

%type <kToken> Program FunDef EndFunDef GlobalDeclare GlobalArray RegInt
%type <kToken> RegOpReg RegOpInt RegUnOpReg RegAssignReg ArrayWrite ArrayRead
%type <kToken> IfStmt GotoLabel LabelDef CallFunc ReturnStmt ProgramArr
%type <kToken> StoreRegInt LoadIntReg LoadVarReg LoadaddrIntReg LoadaddrVarReg

%%
ProgramArr      : Program ProgramArr
                | Program
                ;

Program         : FunDef | EndFunDef | GlobalDeclare | GlobalArray | RegInt | RegOpReg | RegOpInt | RegUnOpReg | RegAssignReg
                | ArrayWrite | ArrayRead | IfStmt | GotoLabel | LabelDef | CallFunc | ReturnStmt | StoreRegInt
                | LoadIntReg | LoadVarReg | LoadaddrIntReg | LoadaddrVarReg
                ;



FunDef          : FNAME LKHZ NUM RKHZ LKHZ NUM RKHZ
                    {
                        if (Debug_Parser)   printf("Trace: FunDef\n");
                        string func_name = (($1)->name).substr(2);
                        code_list.push_back("\t.text");
                        code_list.push_back("\t.align\t2");
                        code_list.push_back("\t.global\t" + func_name);
                        code_list.push_back("\t.type\t" + func_name + ", @function");
                        code_list.push_back(func_name + ":");
                        stk = ((($6)->val)/4 + 1) * 16;

                        if (-stk >= -2048 && -stk <= 2047){
                            code_list.push_back("\taddi\tsp, sp, -" + to_string(stk));
                            code_list.push_back("\tsw\tra, " + to_string(stk-4) + "(sp)");
                        } else{
                            code_list.push_back("li s0, " + to_string(-stk));
                            code_list.push_back("add sp, sp, s0");
                            code_list.push_back("li s0, " + to_string(stk-4));
                            code_list.push_back("add s0, sp, s0");
                            code_list.push_back("\tsw\tra, 0(s0)");
                        }

                    }
                ;

EndFunDef       : END FNAME
                    {
                        if (Debug_Parser)   printf("Trace: FunDef\n");
                        string func_name = (($2)->name).substr(2);
                        code_list.push_back("\t.size\t" + func_name + ", .-" + func_name);
                    }
                ;

GlobalDeclare   : VAR ASSIGN NUM
                    {
                        if (Debug_Parser)   printf("Trace: GlobalDeclare\n");
                        string var_name = ($1)->name;
                        int num = ($3)->val;
                        code_list.push_back("\t.global\t" + var_name);
                        code_list.push_back("\t.section\t.sdata");
                        code_list.push_back("\t.align\t2");
                        code_list.push_back("\t.type\t" + var_name + ", @object");
                        code_list.push_back("\t.size\t" + var_name + ", 4");
                        code_list.push_back(var_name + ":");
                        code_list.push_back("\t.word\t" + to_string(num));
                    }
                ;

GlobalArray     : VAR ASSIGN MALLOC NUM
                    {
                        if (Debug_Parser)   printf("Trace: GlobalArray\n");
                        string var_name = ($1)->name;
                        int num = ($3)->val;
                        code_list.push_back("\t.comm\t" + var_name + ", " + to_string(num) + ", 4");
                    }
                ;

RegInt          : REG ASSIGN NUM 
                    {   
                        if (Debug_Parser)   printf("Trace: RegInt\n");
                        code_list.push_back("li " + ($1)->name + ", " + to_string(($3)->val));
                    }
                ;


RegOpReg        : REG ASSIGN REG Op REG
                    {
                        if (Debug_Parser)   printf("Trace: RegOpReg\n");
                        string reg1 = ($1)->name;
                        string reg2 = ($3)->name;
                        string reg3 = ($5)->name;
                        string op = ($4)->name;
                        genBinOp(reg1, reg2, reg3, op);
                    }
                ;

RegOpInt      : REG ASSIGN REG Op NUM
                    {
                        // 需要分类讨论num的大小，以此使用不同的指令
                        if (Debug_Parser)   printf("Trace: RegOpInt\n");
                        int num = ($5)->val;
                        string op = ($4)->name;
                        if (num >= -2048 && num <= 2047 && op == "+"){
                            code_list.push_back("addi "+ ($1)->name + ", " + ($3)->name + ", " + to_string(num));
                        } else if (num >= -2048 && num <= 2047 && op == "-"){
                            code_list.push_back("addi "+ ($1)->name + ", " + ($3)->name + ", " + to_string(-num));
                        } else if (num >= -2048 && num <= 2047 && op == "<"){
                            code_list.push_back("slti "+ ($1)->name + ", " + ($3)->name + ", " + to_string(num));
                        } else if (num >= -2048 && num <= 2047 && op == "||"){
                            code_list.push_back("ori "+ ($1)->name + ", " + ($3)->name + ", " + to_string(num));
                            code_list.push_back("snez "+ ($1)->name + ", " + ($1)->name);
                        } else{
                            code_list.push_back("li s0, " + to_string(num));
                            genBinOp(($1)->name, ($3)->name, "s0", op);
                        }
                    }
                ;

RegUnOpReg      : REG ASSIGN Op REG
                    {
                        if (Debug_Parser)   printf("Trace: RegUnOpReg\n");
                        string reg1 = ($1)->name;
                        string reg2 = ($4)->name;
                        string op = ($3)->name;
                        if (op == "-"){
                            code_list.push_back("neg " + reg1 + ", " + reg2);
                        } else if (op == "!"){
                            code_list.push_back("seqz " + reg1 + ", " + reg2);
                        } else{
                            printf("Error! Unexpected Operator!\n");
                            code_list.push_back("-----");
                            exit(-1);
                        }
                    }
                ;

RegAssignReg    : REG ASSIGN REG
                    {
                        if (Debug_Parser)   printf("Trace: RegAssignReg\n");
                        code_list.push_back("mv " + ($1)->name + ", " + ($3)->name);
                    }
                ;

ArrayWrite      : REG LKHZ NUM RKHZ ASSIGN REG
                    {
                        if (Debug_Parser)   printf("Trace: ArrayWrite\n");
                        int num = ($3)->val;

                        if (num >= -2048 && num <= 2047){
                            code_list.push_back("sw " + ($6)->name + ", " + to_string(num) + "(" + ($1)->name + ")");
                        } else{
                            code_list.push_back("li s0, " + to_string(num));
                            code_list.push_back("add s0, s0, " + ($1)->name);
                            code_list.push_back("sw " + ($6)->name + ", 0(s0)");
                        }

                    }
                ;

ArrayRead       : REG ASSIGN REG LKHZ NUM RKHZ
                    {
                        if (Debug_Parser)   printf("Trace: ArrayRead\n");
                        int num = ($5)->val;
                        if (num >= -2048 && num <= 2047){
                            code_list.push_back("lw " + ($1)->name + ", " + to_string(num) + "(" + ($3)->name + ")");
                        } else{
                            code_list.push_back("li s0, " + to_string(num));
                            code_list.push_back("add s0, s0, " + ($3)->name);
                            code_list.push_back("lw " + ($1)->name + ", 0(s0)");
                        }
                    }
                ;

IfStmt          : IF REG Op REG GOTO LABEL
                    {
                        if (Debug_Parser)   printf("Trace: IfStmt\n");
                        string reg1 = ($2)->name;
                        string reg2 = ($4)->name;
                        string label = "." + ($6)->name;
                        string op = ($3)->name;
                        if (op == "<"){
                            code_list.push_back("blt " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == ">"){
                            code_list.push_back("bgt " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == "<="){
                            code_list.push_back("ble " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == ">="){
                            code_list.push_back("bge " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == "!="){
                            code_list.push_back("bne " + reg1 + ", " + reg2 + ", " + label);
                        } else if (op == "=="){
                            code_list.push_back("beq " + reg1 + ", " + reg2 + ", " + label);
                        } else {
                            printf("Error! Unexpected Operator!\n");
                            exit(-1);
                        }
                    }
                ;

GotoLabel       : GOTO LABEL
                    {
                        if (Debug_Parser)   printf("Trace: GotoLabel\n");
                        string label = "." + ($2)->name;
                        code_list.push_back("j " + label);
                    }
                ;


LabelDef        : LABEL COLON
                    {
                        if (Debug_Parser)   printf("Trace: LabelDef\n");
                        string label = "." + ($1)->name;
                        code_list.push_back(label + ":");
                    }
                ;

CallFunc        : CALL FNAME
                    {
                        if (Debug_Parser)   printf("Trace: CallFunc\n");
                        string func_name = (($2)->name).substr(2);
                        code_list.push_back("call " + func_name);
                    }
                ;

ReturnStmt      : RETURN
                    {
                        if (Debug_Parser)   printf("Trace: ReturnStmt\n");

                        if (stk >= -2048 && stk <= 2047){
                            code_list.push_back("\tlw\tra, " + to_string(stk-4) + "(sp)");
                            code_list.push_back("\taddi\tsp, sp, " + to_string(stk));
                        } else{
                            code_list.push_back("li s0, " + to_string(stk-4));
                            code_list.push_back("add s0, sp, s0");
                            code_list.push_back("\tlw\tra, 0(s0)");
                            code_list.push_back("li s0, " + to_string(stk));
                            code_list.push_back("add sp, sp, s0");
                        }
                        code_list.push_back("ret");
                    }
                ;

StoreRegInt     : STORE REG NUM
                    {
                        if (Debug_Parser)   printf("Trace: StoreRegInt\n");
                        int num = 4 * ($3)->val;

                        if (num >= -2048 && stk <= 2047){
                            code_list.push_back("sw " + ($2)->name + ", " + to_string(num) + "(sp)");
                        } else{
                            code_list.push_back("li s0, " + to_string(num));
                            code_list.push_back("add s0, sp, s0");
                            code_list.push_back("sw " + ($2)->name + ", 0(s0)");
                        }

                    }
                ;

LoadIntReg      : LOAD NUM REG
                    {
                        if (Debug_Parser)   printf("Trace: LoadIntReg\n");
                        int num = 4 * ($2)->val;

                        if (num >= -2048 && stk <= 2047){
                            code_list.push_back("lw " + ($3)->name + ", " + to_string(num) + "(sp)");
                        } else{
                            code_list.push_back("li s0, " + to_string(num));
                            code_list.push_back("add s0, sp, s0");
                            code_list.push_back("lw " + ($3)->name + ", 0(s0)");
                        }

                    }
                ;

LoadVarReg      : LOAD VAR REG
                    {
                        if (Debug_Parser)   printf("Trace: LoadVarReg\n");
                        string var_name = ($2)->name;
                        string reg = ($3)->name;
                        code_list.push_back("lui " + reg + ", %hi(" + var_name + ")");
                        code_list.push_back("lw " + reg + ", %lo(" + var_name + ")(" + reg + ")");
                    }
                ;

LoadaddrIntReg  : LOADADDR NUM REG
                    {
                        if (Debug_Parser)   printf("Trace: LoadaddrIntReg\n");
                        int num = 4 * ($2)->val;
                        string reg = ($3)->name;
                        if (num >= -2048 && num <= 2047){
                            code_list.push_back("addi " + reg + ", sp, " + to_string(num));
                        } else{
                            code_list.push_back("li s0, " + to_string(num));
                            code_list.push_back("add " + reg + ", sp, s0");
                        }
                    }
                ;

LoadaddrVarReg  : LOADADDR VAR REG
                    {
                        if (Debug_Parser)   printf("Trace: LoadaddrVarReg\n");
                        code_list.push_back("la " + ($3)->name + ", " + ($2)->name);
                    }
                ;


%%

void yyerror(const char *){
    printf("Syntax error at line %d. \n", yylineno);
};

int yywrap(void){
    return 1;
}
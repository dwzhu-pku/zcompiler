%{
    #include<stdio.h>
    #include"eeyore_ast.hpp"
    extern int yylex();
    extern int yylineno;
    extern FILE * yyin;
    extern FILE * yyout;
    void yyerror(BaseAst**, const char *);

    vector<string>code_list;
    vector<string>init_list;
    vector<int>var_list={-1};
    vector<int>param_isarr={0,0,0,0,0,0,0,0};
    map<string, string>global_map;
    map<string, int> stack_map;
    map<string, int> global_isarr;
    map<string, int> stack_isarr;
    int stack_idx = 0;

    int get_next_var(){
        int tmp = var_list.back();
        var_list.push_back(tmp+1);
        return tmp+1;
    }

    int in_func=0;
    int stack_size = 0;
    int param_cnt = 0;
    int reg_idx = 1;
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

%type <kToken> Program Declaration Initialization FunctionDef 
%type <kToken> FunctionHeader FunctionEnd
%type <kToken> Statements Statement Expression RightValue 

%%
Program        : Declaration Program
                    {
                        if (Debug_Parser)   printf("Trace: Program\n");
                    }
                | Initialization  Program
                    {
                        if (Debug_Parser)   printf("Trace: Program\n");
                    }
                | FunctionDef  Program
                    {
                        if (Debug_Parser)   printf("Trace: Program\n");
                    }
                |
                    {
                        if (Debug_Parser)   printf("Trace: Program\n");
                    }
                ;

Declaration     : VAR SYMBOL
                    {
                        string name = ($2)->name;
                        if(in_func){
                            if (stack_map.find(name) != stack_map.end()) {
                                printf("Error! Key Exists!\n");
                            }
                            stack_map[name] = stack_idx;
                            stack_isarr[name] = 0;
                            stack_idx += 1;
                            stack_size += 4; 
                        }else{
                            if (global_map.find(name) != global_map.end()){
                                printf("Error! Key Exists!\n");
                            }
                            string ir_addr = "v" + to_string(get_next_var());
                            global_map[name] = ir_addr;
                            global_isarr[name] = 0;
                            if(Debug_Parser)    printf("name %s, ir_addr %s\n", name.c_str(), ir_addr.c_str());
                            code_list.push_back(ir_addr + " = 0");
                        }
                    }
                | VAR NUM SYMBOL
                    {
                        if (Debug_Parser)   printf("Trace: Declaration\n");
                        string name = ($3)->name;
                        if(in_func){
                            if (stack_map.find(name) != stack_map.end()) {
                                printf("Error! Key Exists!\n");
                            }
                            stack_map[name] = stack_idx;
                            stack_isarr[name] = 1;
                            stack_idx += ($2)->val / 4;
                            stack_size += ($2)->val;
                        }else{
                            if (global_map.find(name) != global_map.end()){
                                printf("Error! Key Exists!\n");
                            }
                            string ir_addr = "v" + to_string(get_next_var());
                            global_map[name] = ir_addr;
                            global_isarr[name] = 1;
                            if(Debug_Parser)    printf("name %s, ir_addr %s\n", name.c_str(), ir_addr.c_str());
                            code_list.push_back(ir_addr + " = malloc " + to_string(($2)->val));
                        }
                    }
                ;

Initialization  : SYMBOL ASSIGN NUM
                    {
                        if (Debug_Parser)   printf("Trace: Initialization\n");
                        string name = ($1)->name;
                        string reg = "t" + to_string(reg_idx++);
                        if(global_map.find(name) != global_map.end()){
                            init_list.push_back("loadaddr " + global_map[name] + " t0");
                            init_list.push_back(reg + " = " + to_string(($3)->val));
                            init_list.push_back("t0[0] = " + reg);
                        }else{
                            init_list.push_back("t0 = " + to_string(($3)->val));
                            init_list.push_back("store t0 " + to_string(stack_map[name]));
                        }
                        reg_idx -= 1;
                    }
                | SYMBOL LKHZ NUM RKHZ ASSIGN NUM
                    {
                        if (Debug_Parser)   printf("Trace: Initialization\n");
                        string name = ($1)->name;
                        string reg = "t" + to_string(reg_idx++);
                        if(global_map.find(name) != global_map.end()){
                            init_list.push_back("loadaddr " + global_map[name] + " t0");
                            init_list.push_back(reg + " = " + to_string(($6)->val));
                            init_list.push_back("t0["+ to_string(($3)->val) + "] = " + reg);
                        }else{
                            init_list.push_back("loadaddr " + to_string(stack_map[name]) + " t0");
                            init_list.push_back("t0 = t0 + " + to_string(($3)->val));
                            init_list.push_back(reg + " = " + to_string(($6)->val));
                            init_list.push_back("t0[0] = " + reg);
                        }
                        reg_idx -= 1;
                    }
                ;

FunctionDef     : FunctionHeader Statements FunctionEnd
                    {
                        ;
                    }
                ;

FunctionHeader  : FNAME LKHZ NUM RKHZ
                    {
                        in_func = 1;
                        param_cnt = 0;
                        stack_idx = 0;
                        stack_size = 0;
                        stack_map.clear();
                        stack_isarr.clear();
                        code_list.push_back(($1)->name + " [" + to_string(($3)->val) + "]");

                        for(int i = 0; i < ($3)->val; ++i){
                            stack_map["p" + to_string(i)] = stack_idx;
                            stack_isarr["p" + to_string(i)] = param_isarr[i]; 
                            code_list.push_back("store a" + to_string(i) + " " + to_string(stack_idx));
                            stack_idx += 1;
                            stack_size += 4;
                        }
                    }
                ;

Statements      : Statement Statements
                    {
                        ;
                    }
                |
                    {
                        ;
                    }
                ;

FunctionEnd     : END FNAME
                    {
                        in_func = 0;
                        for (auto it = code_list.rbegin(); it != code_list.rend(); ++it){
                            if(it->size() >= 2 && it->compare(0,2,"f_") == 0){
                                *it = *it + " [" + to_string(stack_size) + "]";
                                break;
                            }
                        }
                        code_list.push_back("end " + ($2)->name);
                    }
                ;

Statement       : Expression
                    {
                        ;
                    }
                | Declaration
                    {
                        ;
                    }
                ;

Expression      : SYMBOL ASSIGN RightValue Op RightValue
                    {
                        string name = ($1)->name;
                        if(global_map.find(name) != global_map.end()){
                            code_list.push_back("loadaddr " + global_map[name] + " t0");
                            code_list.push_back(($3)->reg + " = " + ($3)->reg + " " + ($4)->name + " " + ($5)->reg);
                            code_list.push_back("t0[0] = " + ($3)->reg);
                        }else{
                            code_list.push_back("t0 = " + ($3)->reg + " " + ($4)->name + " " + ($5)->reg);
                            code_list.push_back("store t0 " + to_string(stack_map[name]));
                        }
                        reg_idx -= 2;
                    }
                | SYMBOL ASSIGN Op RightValue
                    {
                        string name = ($1)->name;
                        if(global_map.find(name) != global_map.end()){
                            code_list.push_back("loadaddr " + global_map[name] + " t0");
                            code_list.push_back("t0[0] = " + ($3)->name + " " + ($4)->reg);
                        }else{
                            code_list.push_back("t0 = " + ($3)->name + " " + ($4)->reg);
                            code_list.push_back("store t0 " + to_string(stack_map[name]));
                        }
                        reg_idx -= 1;
                    }
                | SYMBOL ASSIGN RightValue
                    {
                        string name = ($1)->name;
                        if(global_map.find(name) != global_map.end()){
                            code_list.push_back("loadaddr " + global_map[name] + " t0");
                            code_list.push_back("t0[0] = " + ($3)->reg);
                        }else{
                            code_list.push_back("t0 = " + ($3)->reg);
                            code_list.push_back("store t0 " + to_string(stack_map[name]));
                        }
                        reg_idx -= 1;
                    }
                | SYMBOL LKHZ RightValue RKHZ ASSIGN RightValue
                    {
                        string name = ($1)->name;
                        if(global_map.find(name) != global_map.end()){
                            code_list.push_back("loadaddr " + global_map[name] + " t0");
                            code_list.push_back(($3)->reg + " = " + ($3)->reg + " + t0");
                            code_list.push_back(($3)->reg + "[0] = " + ($6)->reg);
                        }else{
                            if (stack_isarr[name] == 1){
                                code_list.push_back("loadaddr " + to_string(stack_map[name]) + " t0");
                            }else{
                                code_list.push_back("load " + to_string(stack_map[name]) + " t0");
                            }
                            // code_list.push_back("loadaddr " + to_string(stack_map[name]) + " t0");
                            code_list.push_back(($3)->reg + " = " + ($3)->reg + " + t0");
                            code_list.push_back(($3)->reg + "[0] = " + ($6)->reg);
                        }
                        reg_idx -= 2;
                    }
                | SYMBOL ASSIGN SYMBOL LKHZ RightValue RKHZ
                    {
                        string name = ($1)->name;
                        string name2 = ($3)->name;
                        string reg = "t" + to_string(reg_idx++);
                        if(global_map.find(name2) != global_map.end()){
                            if (global_isarr[name2] == 1){
                                code_list.push_back("loadaddr " + global_map[name2] + " " + reg);
                            }else{
                                code_list.push_back("load " + global_map[name2] + " " + reg);
                            }
                        }else{
                            if (stack_isarr[name2] == 1){
                                code_list.push_back("loadaddr " + to_string(stack_map[name2]) + " " + reg);
                            }else{
                                code_list.push_back("load " + to_string(stack_map[name2]) + " " + reg);
                            }
                        }

                        if(global_map.find(name) != global_map.end()){
                            code_list.push_back("loadaddr " + global_map[name] + " t0");
                            code_list.push_back(reg + " = " + reg + " + " + ($5)->reg);
                            code_list.push_back("t0 = " + reg + "[0]");
                        }else{
                            code_list.push_back(reg + " = " + reg + " + " + ($5)->reg);
                            code_list.push_back("t0 = " + reg + "[0]");
                            code_list.push_back("store t0 " + to_string(stack_map[name]));
                        }
                        reg_idx -= 2;
                    }
                | IF RightValue Op RightValue GOTO LABEL
                    {
                        code_list.push_back("if " + ($2)->reg + " " + ($3)->name + " " + ($4)->reg + " goto " + ($6)->name);
                        reg_idx -= 2;
                    }
                | GOTO LABEL
                    {
                        code_list.push_back("goto " + ($2)->name);
                    }
                | LABEL COLON
                    {
                        code_list.push_back (($2)->name + ":");
                    }
                | PARAM RightValue
                    {
                        string name = ($2)->name;
                        if(global_isarr.find(name) != global_isarr.end()){
                            if(global_isarr[name] == 1){
                                param_isarr[param_cnt] = 1;
                            }else{
                                param_isarr[param_cnt] = 0;
                            }
                        }else{
                            if (stack_isarr[name] == 1){
                                param_isarr[param_cnt] = 1;
                            }else{
                                param_isarr[param_cnt] = 0;
                            }
                        }
                        code_list.push_back("a" + to_string(param_cnt) + " = " + ($2)->reg);
                        param_cnt += 1;
                        reg_idx -= 1;
                    }
                | CALL FNAME
                    {
                        param_cnt = 0;
                        code_list.push_back("call " + ($2)->name);
                    }
                | SYMBOL ASSIGN CALL FNAME
                    {
                        param_cnt = 0;
                        code_list.push_back("call " + ($4)->name);
                        string name = ($1)->name;
                        if(global_map.find(name) != global_map.end()){
                            code_list.push_back("loadaddr " + global_map[name] + " t0");
                            code_list.push_back("t0[0] = a0");
                        }else{
                            code_list.push_back("t0 = a0");
                            code_list.push_back("store t0 " + to_string(stack_map[name]));
                        }
                    }
                | RETURN RightValue
                    {
                        code_list.push_back("a0 = " + ($2)->reg);
                        code_list.push_back("return");
                        reg_idx -= 1;
                    }
                | RETURN
                    {
                        code_list.push_back("return");
                    }
                ;


RightValue      : SYMBOL
                    {
                        string name = ($1)->name;
                        string reg = "t" + to_string(reg_idx++);

                        if(global_map.find(name) != global_map.end()){
                            if (global_isarr[name] == 1){
                                code_list.push_back("loadaddr " + global_map[name] + " " + reg);
                            }else{
                                code_list.push_back("load " + global_map[name] + " " + reg);
                            }
                        }else{
                            if (stack_isarr[name] == 1){
                                code_list.push_back("loadaddr " + to_string(stack_map[name]) + " " + reg);
                            }else{
                                code_list.push_back("load " + to_string(stack_map[name]) + " " + reg);
                            }
                        }
                        ($1)->reg = reg;
                        $$ = $1;
                    }
                | NUM
                    {
                        string reg = "t" + to_string(reg_idx++);
                        code_list.push_back(reg + " = " + to_string(($1)->val));
                        ($1)->reg = reg;
                        $$ = $1;
                    }
                ;

%%

void yyerror(BaseAst**, const char *){
    printf("Syntax error at line %d. \n", yylineno);
};

int yywrap(void){
    return 1;
}
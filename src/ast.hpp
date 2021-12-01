#ifndef AST_H_
#define AST_H_

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>
#include"sym.hpp"

using namespace std;

#define Debug_Lex 0
#define Debug_Parser 0
#define Debug_Ir 0

extern vector<string>code_list;
extern vector<int>label_list;
extern vector<int>native_list;
extern vector<int>temp_list;

extern string str_t;
extern string str_T;

extern int temp_index;
extern int native_index;
extern int code_index;

class Token{
    public:
        int token_type;
        int val;
        string ident_name;
        int line_no;

        Token(int token_type_, int val_, int line_no_){
            token_type = token_type_;
            val = val_;
            line_no = line_no_;
        }
        Token(int token_type_, const string & ident_name_, int line_no_){
            token_type = token_type_;
            ident_name = ident_name_;
            line_no = line_no_;
        }
};

enum class AstType{
    kAssign, kDecl, kFunDef, kFunCall, kBlock, 
    kIf, kWhile, kBreak, kContinue, kReturn,
    kBinaryOp, kUnaryOp, kBase, kArray, kLval, kList
};



/*所有Ast节点的基类*/
class BaseAst {
    public:
        virtual ~BaseAst() = default;
        virtual void genCode(){}
        virtual int calVal(){return 0;}

        AstType node_type; // 节点类型
        string addr;
        int is_const; // 0: false; 1: true
        int val;

        string branch1;
        string branch2;
        string next;
};

extern stack<BaseAst*>while_list;

/*变量引用*/
class LvalAst: public BaseAst{
    public:
        string name;
        vector<BaseAst*> list_dims;
        int is_left_val;

        LvalAst(const string & name_){
            node_type = AstType::kLval;
            name = name_;
        }

        LvalAst(const string & name_, vector<BaseAst*> & list_dims_){
            node_type = AstType::kLval;
            name = name_;
            for(auto i: list_dims_){
                list_dims.push_back(i);
            }
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for LvalAst\n" );
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(name);
            if( item == cur->end()){
                printf("Error! Token not in this symbol table!\n");
                return;
            }
            addr = item->second->ir_name;
            vector<int>offset_vec = item->second->offset_vec;
            
            /*此时，该引用为数组*/
            if (offset_vec.size() > 0){
                int tmp = temp_list.back();
                temp_list.push_back(tmp+1);
                temp_list.push_back(tmp+2);
                string add_tmp = str_t + to_string(tmp+1);
                string mul_tmp = str_t + to_string(tmp+2);
                code_list.push_back( "var " + add_tmp);
                code_list.push_back( "var " + mul_tmp);
                code_list.push_back( add_tmp  + " = 0" );

                for(int i = 0; i < int(list_dims.size()); ++i){
                    list_dims[i]->genCode();
                    code_list.push_back(mul_tmp + " = " + to_string(offset_vec[i+1]) + " * " + list_dims[i]->addr);
                    code_list.push_back(add_tmp + " = " + add_tmp + " + " + mul_tmp );
                }
                code_list.push_back(add_tmp + " = " + add_tmp + " * 4");
                if(list_dims.size() + 1 == offset_vec.size()){
                    addr = addr + "[" + add_tmp + "]";
                }
                else{
                    int tmp = temp_list.back();
                    temp_list.push_back(tmp+1);
                    string sum_tmp = str_t + to_string(tmp+1);
                    code_list.push_back( "var " + sum_tmp);
                    code_list.push_back( sum_tmp  + " = 0" );
                    code_list.push_back( sum_tmp + " = " + addr + " + " + add_tmp);
                    addr = sum_tmp;
                }
                if(is_left_val == 0){
                    tmp = temp_list.back();
                    temp_list.push_back(tmp+1);
                    string var_tmp = str_t + to_string(tmp+1);
                    code_list.push_back( "var " + var_tmp);
                    code_list.push_back(var_tmp + " = " + addr);
                    addr = var_tmp;
                }
            }
            if(!(branch1 == "" && branch2 == "" && next == "")){
                string code_line =  "if " + addr + " != 0 goto " + branch1;
                code_list.push_back(code_line);
                code_list.push_back("goto " + branch2);
            }
        }

        int calVal(){
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(name);
            if( item == cur->end()){
                printf("Error! Token not in this symbol table!\n");
                return 0;
            }
            if (item->second->ident_type != 2){ // 如果不是const，报错
                printf("Error! Token is not a const" );
                return 0;
            }
            if (list_dims.size() > 0){ // 数组
                int tmp_ofs = 0;
                for(int i = 0; i < int(list_dims.size()); ++i){
                    int tmp_dim = list_dims[i]->calVal();
                    tmp_ofs += tmp_dim * item->second->offset_vec[i+1];
                }
                return item->second->init_val_list[tmp_ofs];
            }else{ // 变量
                return item->second->init_val_list[0];
            }

        }

};

/*赋值语句*/
class AssignAst: public BaseAst{
    public:
        BaseAst* lval;
        BaseAst* exp; //有可能是表达式，也有可能是数值

        AssignAst(BaseAst* lval_, BaseAst* exp_){
            node_type = AstType::kAssign;
            lval = lval_;
            exp = exp_;
        }
        void genCode(){
            if (Debug_Ir) printf("Generating code for AssignAst\n");
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(dynamic_cast<LvalAst*>(lval)->name);
            if( item == cur->end()){
                printf("Error! Token not in this symbol table!\n");
                return;
            }
            lval->genCode();
            exp->genCode();
            string code_line = lval->addr + " = " + exp->addr;
            code_list.push_back(code_line);
        }

};

/*声明语句*/
class DeclAst: public BaseAst{
    public:
        int var_type;
        string name;
        BaseAst* exp; //有可能是表达式，也有可能是数值

        DeclAst(int var_type_ , const string & name_){
            node_type = AstType::kDecl;
            var_type = var_type_;
            name = name_;
        }
        DeclAst(int var_type_ , const string & name_, BaseAst* exp_){
            node_type = AstType::kDecl;
            var_type = var_type_;
            name = name_;
            exp = exp_;
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for DeclAst\n");
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(name);
            if( item != cur->end()){
                printf("Token already declared in this symbol table, Override!\n");
            }
            int tmp = native_list.back();
            native_list.push_back(tmp+1);
            addr = str_T + to_string(tmp+1);
            code_list.push_back( "var " + addr);

            if(is_const == 0){
                SymItem* ptr = new SymItem(name, addr, var_type, 0);
                (*cur)[name]=ptr;
                if(exp!=nullptr){
                    exp->genCode();
                    string code_line =  addr + " = " + exp->addr;
                    code_list.push_back(code_line);
                }
            }else{ //如果是const，需要在符号表中写入初值
                SymItem* ptr = new SymItem(name, addr, 2, 0);
                int tmp_val = exp->calVal();
                ptr->init_val_list.push_back(tmp_val);
                (*cur)[name]=ptr;
                code_list.push_back(addr +  " = " + to_string(tmp_val));
            }
            return ;
        }

};



/*函数相关*/

class FunDefAst: public BaseAst{
    public:
        int var_type;
        string name;
        BaseAst* fun_body;
        vector<BaseAst*> fun_params; //形参

        FunDefAst(int var_type_, const string & name_, BaseAst* fun_body_){
            node_type = AstType::kFunDef;
            var_type = var_type_;
            name = name_;
            fun_body = fun_body_;
        }

        FunDefAst(int var_type_, const string & name_, BaseAst* fun_body_, vector<BaseAst*> & fun_params_){
            node_type = AstType::kFunDef;
            var_type = var_type_;
            name = name_;
            fun_body = fun_body_;
            for(auto i: fun_params_){
                fun_params.push_back(i);
            }
        }
        void genCode();

};

class FunCallAst: public BaseAst{
    public:
        string name;
        vector<BaseAst*> fun_params; //实参

        FunCallAst(const string & name_){
            node_type = AstType::kFunCall;
            name = name_;
        }
        FunCallAst(const string & name_, vector<BaseAst*> & fun_params_){
            node_type = AstType::kFunCall;
            name = name_;
            for(auto i: fun_params_){
                fun_params.push_back(i);
            }
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for FunCallAst\n");
            auto item = fun_sym_table.find(name);
            if( item == fun_sym_table.end()){
                printf("Error! Function not declared in this symbol table!\n");
                return;
            }
            for (auto para: fun_params){
                para->genCode();
                code_list.push_back("param " + para->addr);
            }
            // void
            if (item->second->ident_type == 0){
                code_list.push_back("call " + item->second->ir_name );
            }else{ // int
                int tmp = temp_list.back();
                temp_list.push_back(tmp + 1);
                addr = str_t + to_string(tmp + 1);
                code_list.push_back( "var " + addr);
                code_list.push_back( addr + " = call " + item->second->ir_name );
            }
        }
};

class ArrayAst: public BaseAst{
    public:
        vector<BaseAst*> array_list; //实参

        void append_item(BaseAst* ptr){
            array_list.push_back(ptr);
        }

        ArrayAst(){
            node_type = AstType::kArray;
        }
        ArrayAst(vector<BaseAst*> & array_list_){
            node_type = AstType::kArray;
            for(auto i: array_list_){
                array_list.push_back(i);
            }
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for ArrayAst\n");
            for(auto i: array_list){
                i->is_const = is_const;
                i->genCode();
            }
        }

};


/*语句块*/
class BlockAst: public BaseAst{
    public:
        vector<BaseAst*> list_stmts;

        BlockAst(){
            node_type = AstType::kBlock;
        }
        BlockAst(vector<BaseAst*> &list_stmts_){
            node_type = AstType::kBlock;
            for(auto i: list_stmts_){
                list_stmts.push_back(i);
            }
        }

        void append_stmt(BaseAst* ast_ptr){
            list_stmts.push_back(ast_ptr);
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for BlockAst\n");
            for(auto i: list_stmts){
                i->genCode();
            }
        }
};

/*控制流相关*/

class IfAst: public BaseAst{
    public:
        BaseAst* if_cond;
        BaseAst* if_then_stmt;
        BaseAst* else_stmt;

        IfAst(BaseAst* if_cond_, BaseAst* if_then_stmt_, BaseAst* else_stmt_){
            node_type = AstType::kIf;
            if_cond = if_cond_;
            if_then_stmt = if_then_stmt_;
            else_stmt = else_stmt_;
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for IfAst\n");
            int tmp = label_list.back();
            label_list.push_back(tmp+1);
            label_list.push_back(tmp+2);
            label_list.push_back(tmp+3);
            branch1 = "l" + to_string(tmp+1);
            branch2 = "l" + to_string(tmp+2);
            next = "l" + to_string(tmp+3);

            if_cond->branch1 = branch1;
            if_cond->branch2 = branch2;
            if_cond->next = next;
            if_cond->genCode();

            code_list.push_back( branch1 + ":");
            if(if_then_stmt != nullptr){
                if_then_stmt->genCode();
            }
            code_list.push_back( "goto " + next);
            code_list.push_back( branch2 + ":");
            if(else_stmt != nullptr){
                else_stmt->genCode();
            }
            code_list.push_back( "goto " + next);
            code_list.push_back( next + ":");

        }
};

class WhileAst: public BaseAst{
    public:
        BaseAst* while_cond;
        BaseAst* while_stmt;

        WhileAst(BaseAst* while_cond_, BaseAst* while_stmt_){
            node_type = AstType::kWhile;
            while_cond = while_cond_;
            while_stmt = while_stmt_;
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for WhileAst\n");
            while_list.push(this);
            int tmp = label_list.back();
            label_list.push_back(tmp+1);
            label_list.push_back(tmp+2);
            label_list.push_back(tmp+3);
            branch1 = "l" + to_string(tmp+1);
            branch2 = "l" + to_string(tmp+2);
            next = "l" + to_string(tmp+3);

            code_list.push_back( branch1 + ":");

            while_cond->branch1 = branch2;
            while_cond->branch2 = next;
            while_cond->next = next;
            while_cond->genCode();

            // string code_line =  "if " + while_cond->addr + " == 1\tgoto " + branch2;
            // code_list.push_back(code_line);

            // code_list.push_back( "goto " + next);
            code_list.push_back( branch2 + ":");

            while_stmt->genCode();
            code_list.push_back( "goto " + branch1);

            code_list.push_back( next + ":");

            while_list.pop();
        }


};

class BreakAst: public BaseAst{
    public:
        BreakAst(){
            node_type = AstType::kBreak;
        }
        void genCode(){
            if (Debug_Ir) printf("Generating code for BreakAst\n");
            next = while_list.top()->next;
            code_list.push_back( "goto "+ next);
        }
};

class ContinueAst: public BaseAst{
    public:
        ContinueAst(){
            node_type = AstType::kContinue;
        }
        void genCode(){
            if (Debug_Ir) printf("Generating code for ContinueAst\n");
            next = while_list.top()->branch1;
            code_list.push_back( "goto "+ next);
        }
};

class ReturnAst: public BaseAst{
    public:
        BaseAst* next;
        BaseAst* exp;

        ReturnAst(BaseAst* next_, BaseAst* exp_){
            node_type = AstType::kReturn;
            next = next_;
            exp = exp_;
        }
        void genCode(){
            if (Debug_Ir) printf("Generating code for ReturnAst\n");
            if(exp == nullptr){
                code_list.push_back( "return");
            }else{
                exp->genCode();
                code_list.push_back( "return " + exp->addr);
            }
        }
};


/*运算符相关*/

class BinaryOpAst: public BaseAst{
    public:
        BaseAst* lt_exp;
        BaseAst* rt_exp;
        string op;

        BinaryOpAst(BaseAst* astptr_lt, BaseAst* astptr_rt, const string & op_, int val_, int is_const_){
            node_type = AstType::kBinaryOp;
            lt_exp = astptr_lt;
            rt_exp = astptr_rt;
            op = op_;
            val = val_;
            is_const = is_const_;
            branch1 = "";
            branch2 = "";
            next = "";
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for BinaryAst\n");
            if(lt_exp == nullptr && rt_exp == nullptr){
                addr = to_string(val);
                if (!(branch1 == "" && branch2 == "" && next == "")){
                    string code_line = "if " + addr + " != 0 goto " + branch1;
                    code_list.push_back(code_line);
                    code_list.push_back("goto " + branch2);
                }
            }else if(lt_exp == nullptr && rt_exp != nullptr){
                rt_exp->genCode();
                addr = rt_exp->addr;
            }else if(lt_exp != nullptr && rt_exp == nullptr){
                lt_exp->genCode();
                addr = lt_exp->addr;
            }else if(op == "||"){
                lt_exp->branch1 = branch1;
                rt_exp->branch1 = branch1;
                rt_exp->branch2 = branch2;
                int tmp = label_list.back();
                label_list.push_back(tmp+1);
                lt_exp->branch2 = "l" + to_string(tmp+1);
                lt_exp->genCode();
                code_list.push_back( lt_exp->branch2 + ":");
                rt_exp->genCode();
            }else if(op == "&&"){
                int tmp = label_list.back();
                label_list.push_back(tmp+1);
                lt_exp->branch1 = "l" + to_string(tmp+1);
                lt_exp->branch2 = branch2;
                rt_exp->branch1 = branch1;
                rt_exp->branch2 = branch2;
                lt_exp->genCode();
                code_list.push_back( lt_exp->branch1 + ":");
                rt_exp->genCode();
            }else{
                lt_exp->genCode();
                rt_exp->genCode();

                int tmp = temp_list.back();
                temp_list.push_back(tmp + 1);
                addr = str_t + to_string(tmp + 1);
                code_list.push_back( "var " + addr);

                code_list.push_back(addr + " = " + lt_exp->addr + " " + op + " " + rt_exp->addr);
                if(!(branch1 == "" && branch2 == "" && next == "")){
                    code_list.push_back("if " + addr + " != 0 goto " + branch1);
                    code_list.push_back("goto " + branch2);
                }
            }
        }

        int calVal(){
            if(is_const){
                return val;
            }else if (lt_exp == nullptr && rt_exp != nullptr){
                return rt_exp->calVal();
            }else if (lt_exp != nullptr && rt_exp == nullptr){
                return lt_exp->calVal();
            }else{
                int tmp1 = lt_exp->calVal();
                int tmp2 = rt_exp->calVal();
                if (op == "+"){
                    return tmp1 + tmp2;
                }else if (op == "-"){
                    return tmp1 - tmp2;
                }else if (op == "*"){
                    return tmp1 * tmp2;
                }else if (op == "/"){
                    return tmp1 * tmp2;
                }else if (op == "%"){
                    return tmp1 % tmp2;
                }else{
                    return 0;
                }
            }
            
        }

};

class UnaryOpAst: public BaseAst{
    public:
        BaseAst* exp;
        string op;

        UnaryOpAst(BaseAst* astptr, const string & op_){
            node_type = AstType::kUnaryOp;
            exp = astptr;
            op = op_;
        }
        void genCode(){
            // 不在 if cond 中时的行为
            if(branch1 == "" && branch2 == "" && next == ""){
                exp->genCode();
                int tmp = temp_list.back();
                temp_list.push_back(tmp + 1);
                addr = str_t + to_string(tmp + 1);
                code_list.push_back( "var " + addr);
                if(op != "+"){
                    code_list.push_back(addr + " = " + op + exp->addr);
                }else{
                    code_list.push_back( addr + " = " + exp->addr);
                }
            }else{ //在if cond中时的行为
                if(op == "+" || op == "-"){
                    exp->branch1 = branch1;
                    exp->branch2 = branch2;
                    exp->next = next;
                    exp->genCode();
                }else{
                    exp->branch1 = branch2;
                    exp->branch2 = branch1;
                    exp->next = next;
                    exp->genCode();
                }
            }
        }

        int calVal(){
            int tmp = exp->calVal();
            if(op == "+"){
                return tmp; 
            }else if(op == "-"){
                return -tmp;
            }else{
                return 0;
            }
        }
};

/* 数组 */
class ListAst: public BaseAst{
    public:
        string name;
        vector<BaseAst*> list_dims;
        vector<BaseAst*> list_inits;
        vector<int> dim_vec;
        vector<int> offset_vec;
        vector<int> init_val_vec;
        int list_size = 0;


        
        ListAst(const string & name_ ){
            node_type = AstType::kList;
            name = name_;
        }

        ListAst(const string & name_ , vector<BaseAst*> & list_dims_){
            node_type = AstType::kList;
            name = name_;
            for(auto i: list_dims_){
                list_dims.push_back(i);
            }
        }
        
        ListAst(const string & name_ , vector<BaseAst*> & list_dims_, vector<BaseAst*> & list_inits_){
            node_type = AstType::kList;
            name = name_;
            for(auto i: list_dims_){
                list_dims.push_back(i);
            }
            for(auto i: list_inits_){
                list_inits.push_back(i);
            }
        }

        void get_dim_offset(){
            for (auto i : list_dims){
                dim_vec.push_back(i->calVal());
            }
            int sz = 1;
            for (int i: dim_vec){
                sz *= i;
            }
            int mul = 1;
            offset_vec.push_back(sz);
            for (int i: dim_vec){
                mul = mul * i;
                offset_vec.push_back(sz/mul);
            }
            list_size = sz*4;
            return ;
        }
        
        void genCode(){
            if (Debug_Ir) printf("Generating code for ListAst\n");
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(name);
            if( item != cur->end()){
                printf("Token already declared in this symbol table, Override!\n");
            }
            int tmp = native_list.back();
            native_list.push_back(tmp+1);
            addr = str_T + to_string(tmp+1);
            
            /* 数组相关计算 */
            get_dim_offset();

            /* 数组声明 */
            code_list.push_back( "var " + to_string(list_size) + " " +  addr);

            if(is_const){
                SymItem* ptr = new SymItem(name, addr, 2, 0, offset_vec);
                init_val_vec.resize(list_size/4, 0);
                get_init_val(list_inits, 0, 0);
                ptr->init_val_list = init_val_vec;
                (*cur)[name]=ptr;
            }else{
                SymItem* ptr = new SymItem(name, addr, 1, 0, offset_vec);
                (*cur)[name]=ptr;
                /* 数组初始化 */
                set_init_val(list_inits, 0, 0);
            }

        }

        void set_init_val(vector<BaseAst*> & init_vec, int level, int st){
            int ofs = st;
            for(int i=0; i < int(init_vec.size()); ++i){
                if(init_vec[i]->node_type == AstType::kArray){
                    set_init_val(dynamic_cast<ArrayAst*>(init_vec[i])->array_list, level+1, ofs);
                    ofs += offset_vec[level+1];
                }else{
                    init_vec[i]->genCode();
                    string code_line = addr + "[" + to_string(4*ofs) + "] = " + init_vec[i]->addr;
                    code_list.push_back(code_line);
                    ofs += 1;
                }
            }
            for(int i = ofs; i < st + offset_vec[level];++i){
                string code_line = addr + "[" + to_string(4*i) + "] = 0";
                code_list.push_back(code_line);
            }
        }

        void get_init_val(vector<BaseAst*> & init_vec, int level, int st){
            int ofs = st;
            for(int i=0; i < int(init_vec.size()); ++i){
                if(init_vec[i]->node_type == AstType::kArray){
                    set_init_val(dynamic_cast<ArrayAst*>(init_vec[i])->array_list, level+1, ofs);
                    ofs += offset_vec[level+1];
                }else{
                    init_val_vec[ofs] = init_vec[i]->calVal();
                    code_list.push_back(addr + "[" + to_string(4*ofs) + "] = " + to_string(init_val_vec[ofs]));
                    ofs += 1;
                }
            }
        }

};


#endif /* AST_H_ */


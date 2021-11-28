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
    kBinaryOp, kUnaryOp, kBase, kArray, kLval
};



/*所有Ast节点的基类*/
class BaseAst {
    public:
        virtual ~BaseAst() = default;
        virtual void genCode(){}

        AstType node_type; // 节点类型
        string addr;

        string branch1;
        string branch2;
        string next;
};

extern stack<BaseAst*>while_list;

/*赋值语句*/
class AssignAst: public BaseAst{
    public:
        string name;
        BaseAst* exp; //有可能是表达式，也有可能是数值

        AssignAst(const string &name_, BaseAst* exp_){
            node_type = AstType::kAssign;
            name = name_;
            exp = exp_;
        }
        void genCode(){
            if (Debug_Ir) printf("Generating code for AssignAst\n");
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(name);
            if( item == cur->end()){
                printf("Error! Token not in this symbol table!\n");
                return;
            }
            exp->genCode();
            string code_line = item->second->ir_name + " = " + exp->addr;
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
                printf("Error! Token already declared in this symbol table!\n");
                return;
            }
            int tmp = native_list.back();
            native_list.push_back(tmp+1);
            addr = str_T + to_string(tmp+1);
            code_list.push_back( "var " + addr);
            SymItem* ptr = new SymItem(name, addr, var_type, 0);
            cur->insert(make_pair(name, ptr));
            if(exp!=nullptr){
                exp->genCode();
                string code_line =  addr + " = " + exp->addr;
                code_list.push_back(code_line);
            }
            return ;
        }

};

/*变量引用*/
class LvalAst: public BaseAst{
    public:
        string name;
        LvalAst(const string & name_){
            node_type = AstType::kLval;
            name = name_;
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for LvalAst\n");
            SymTable* cur = var_sym_stack.top();
            auto item = cur->find(name);
            if( item == cur->end()){
                printf("Error! Token not in this symbol table!\n");
                return;
            }
            addr = item->second->ir_name;
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

        void genCode(){
            if (Debug_Ir) printf("Generating code for FunDefAst\n");

            // temp_index = temp_list.back();
            // native_index = native_list.back();
            // code_index = int(code_list.size());

            auto item = fun_sym_table.find(name);
            if( item != fun_sym_table.end()){
                printf("Error! Function already declared in this symbol table!\n");
                return;
            }
            addr = "f_" + name;
            SymItem* ptr = new SymItem(name, addr, var_type, 1);
            fun_sym_table.insert(make_pair(name, ptr));
            SymTable* map_ptr = new SymTable();
            if(var_sym_stack.size() > 0)
                *map_ptr = *(var_sym_stack.top());
            var_sym_stack.push(map_ptr);
            SymTable* cur = var_sym_stack.top();

            string code_line =  "f_" + name + "[" + to_string(fun_params.size()) + "]";
            code_list.push_back(code_line);

            int i = 0;
            for(auto para:fun_params){
                para->addr = "p" + to_string(i);
                i += 1;
                SymItem* tmp_ptr = new SymItem(((DeclAst*)para)->name, para->addr, ((DeclAst*)para)->var_type, 0);
                cur->insert(make_pair(((DeclAst*)para)->name,tmp_ptr));
            }
            
            fun_body->genCode();

            var_sym_stack.pop();

            code_list.push_back( "end " + addr);

            // for(int i = temp_index+1; i <= temp_list.back(); ++i){
            //     code_list.insert(code_list.begin() + code_index + 1, string(level+1,'\t') + "var t" + to_string(i));
            // }

            // for(int i = native_index+1; i <= native_list.back(); ++i){
            //     code_list.insert(code_list.begin() + code_index + 1, string(level+1,'\t') + "var T" + to_string(i));
            // }

        }
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

        void genCode(){
            if (Debug_Ir) printf("Generating code for ArrayAst\n");
            for(auto i: array_list){
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

            if_cond->genCode();

            string code_line =  "if " + if_cond->addr + " == 1\tgoto " + branch1;
            code_list.push_back(code_line);

            code_list.push_back( "goto " + branch2);
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

            while_cond->genCode();

            string code_line =  "if " + while_cond->addr + " == 1\tgoto " + branch2;
            code_list.push_back(code_line);

            code_list.push_back( "goto " + next);
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
        int val;
        int is_const;

        BinaryOpAst(BaseAst* astptr_lt, BaseAst* astptr_rt, const string & op_, int val_, int is_const_){
            node_type = AstType::kBinaryOp;
            lt_exp = astptr_lt;
            rt_exp = astptr_rt;
            op = op_;
            val = val_;
            is_const = is_const_;
        }

        void genCode(){
            if (Debug_Ir) printf("Generating code for BinaryAst\n");
            if(lt_exp == nullptr && rt_exp == nullptr){
                addr = to_string(val);
            }else if(lt_exp == nullptr && rt_exp != nullptr){
                rt_exp->genCode();
                addr = rt_exp->addr;
            }else if(lt_exp != nullptr && rt_exp == nullptr){
                lt_exp->genCode();
                addr = lt_exp->addr;
            }else{
                lt_exp->genCode();
                rt_exp->genCode();
                int tmp = temp_list.back();
                temp_list.push_back(tmp + 1);
                addr = str_t + to_string(tmp + 1);
                code_list.push_back( "var " + addr);
                string code_line =  addr + " = " + lt_exp->addr + " " + op + " " + rt_exp->addr;
                code_list.push_back(code_line);
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
            exp->genCode();
            if(op != "+"){
                int tmp = temp_list.back();
                temp_list.push_back(tmp + 1);
                addr = str_t + to_string(tmp + 1);
                code_list.push_back( "var " + addr);
                string code_line =  addr + " = " + op + exp->addr;
                code_list.push_back(code_line);
            }
        }
};


#endif /* AST_H_ */


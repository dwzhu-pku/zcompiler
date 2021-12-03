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
        AstType node_type; // 节点类型
        string addr;
        int is_const; // 0: false; 1: true
        int val;
        int lineno;

        string branch1;
        string branch2;
        string next;

        virtual ~BaseAst() = default;
        virtual void genCode(){} //生成代码
        virtual int calVal(){return 0;} // 计算值
};

/*变量引用*/
class LvalAst: public BaseAst{
    public:
        string name;
        vector<BaseAst*> list_dims;
        int is_left_val;

        void genCode();
        int calVal();

        LvalAst(const string & name_){
            node_type = AstType::kLval;
            name = name_;
        }

        LvalAst(const string & name_, vector<BaseAst*> & list_dims_){
            node_type = AstType::kLval;
            name = name_;
            list_dims = list_dims_;
        }
};

/*赋值语句*/
class AssignAst: public BaseAst{
    public:
        BaseAst* lval;
        BaseAst* exp; //有可能是表达式，也有可能是数值

        void genCode();

        AssignAst(BaseAst* lval_, BaseAst* exp_){
            node_type = AstType::kAssign;
            lval = lval_;
            exp = exp_;
        }

};

/*声明语句*/
class DeclAst: public BaseAst{
    public:
        int var_type;
        string name;
        BaseAst* exp; //有可能是表达式，也有可能是数值

        void genCode();

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


};



/*函数相关*/

class FunDefAst: public BaseAst{
    public:
        int var_type;
        string name;
        BaseAst* fun_body;
        vector<BaseAst*> fun_params; //形参

        void genCode();

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
            fun_params = fun_params_;
        }

};

class FunCallAst: public BaseAst{
    public:
        string name;
        vector<BaseAst*> fun_params; //实参

        void genCode();

        FunCallAst(const string & name_){
            node_type = AstType::kFunCall;
            name = name_;
        }

        FunCallAst(const string & name_, vector<BaseAst*> & fun_params_){
            node_type = AstType::kFunCall;
            name = name_;
            fun_params = fun_params_;
        }

};

class ArrayAst: public BaseAst{
    public:
        vector<BaseAst*> array_list; //实参

        void genCode();
        void append_item(BaseAst* ptr){
            array_list.push_back(ptr);
        }

        ArrayAst(){
            node_type = AstType::kArray;
        }
        ArrayAst(vector<BaseAst*> & array_list_){
            node_type = AstType::kArray;
            array_list = array_list_;
        }


};


/*语句块*/
class BlockAst: public BaseAst{
    public:
        vector<BaseAst*> list_stmts;

        void genCode();
        void append_stmt(BaseAst* ast_ptr){
            list_stmts.push_back(ast_ptr);
        }

        BlockAst(){
            node_type = AstType::kBlock;
        }

        BlockAst(vector<BaseAst*> &list_stmts_){
            node_type = AstType::kBlock;
            list_stmts = list_stmts_;
        }


};

/*控制流相关*/

class IfAst: public BaseAst{
    public:
        BaseAst* if_cond;
        BaseAst* if_then_stmt;
        BaseAst* else_stmt;

        void genCode();

        IfAst(BaseAst* if_cond_, BaseAst* if_then_stmt_, BaseAst* else_stmt_){
            node_type = AstType::kIf;
            if_cond = if_cond_;
            if_then_stmt = if_then_stmt_;
            else_stmt = else_stmt_;
        }

};

class WhileAst: public BaseAst{
    public:
        BaseAst* while_cond;
        BaseAst* while_stmt;

        void genCode();

        WhileAst(BaseAst* while_cond_, BaseAst* while_stmt_){
            node_type = AstType::kWhile;
            while_cond = while_cond_;
            while_stmt = while_stmt_;
        }


};

class BreakAst: public BaseAst{
    public:
        void genCode();
        BreakAst(){
            node_type = AstType::kBreak;
        }
};

class ContinueAst: public BaseAst{
    public:
        void genCode();
        ContinueAst(){
            node_type = AstType::kContinue;
        }
};

class ReturnAst: public BaseAst{
    public:
        BaseAst* next;
        BaseAst* exp;

        void genCode();

        ReturnAst(BaseAst* next_, BaseAst* exp_){
            node_type = AstType::kReturn;
            next = next_;
            exp = exp_;
        }
};


/*运算符相关*/

class BinaryOpAst: public BaseAst{
    public:
        BaseAst* lt_exp;
        BaseAst* rt_exp;
        string op;

        void genCode();
        int calVal();

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
};

class UnaryOpAst: public BaseAst{
    public:
        BaseAst* exp;
        string op;

        void genCode();
        int calVal();

        UnaryOpAst(BaseAst* astptr, const string & op_){
            node_type = AstType::kUnaryOp;
            exp = astptr;
            op = op_;
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
        void genCode();
        
        ListAst(const string & name_ ){
            node_type = AstType::kList;
            name = name_;
        }

        ListAst(const string & name_ , vector<BaseAst*> & list_dims_){
            node_type = AstType::kList;
            name = name_;
            list_dims = list_dims_;
        }
        
        ListAst(const string & name_ , vector<BaseAst*> & list_dims_, vector<BaseAst*> & list_inits_){
            node_type = AstType::kList;
            name = name_;
            list_dims = list_dims_;
            list_inits = list_inits_;
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
                    get_init_val(dynamic_cast<ArrayAst*>(init_vec[i])->array_list, level+1, ofs);
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


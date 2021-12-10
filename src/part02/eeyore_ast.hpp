#ifndef AST_H_
#define AST_H_

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>

using namespace std;

#define Debug_Lex 0
#define Debug_Parser 0
#define Debug_Ir 0

extern vector<string>code_list;
extern vector<string>init_list;
extern vector<int>var_list;
extern map<string, int> stack_map;
extern map<string, string>global_map;
extern int stack_idx;
extern int stack_size;
extern int param_cnt;

int get_next_var();

class Token{
    public:
        int token_type;
        int val = 0;
        string name = "";
        string ir_addr = "";
        string reg = "";
        int line_no = 0;

        Token(){
            ;
        }
        Token(int token_type_, int val_, int line_no_){
            token_type = token_type_;
            val = val_;
            line_no = line_no_;
        }
        Token(int token_type_, const string & name_, int line_no_){
            token_type = token_type_;
            name = name_;
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


#endif /* AST_H_ */


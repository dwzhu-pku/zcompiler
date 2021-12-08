#ifndef AST_H_
#define AST_H_

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>

using namespace std;

#define Debug_Lex 1
#define Debug_Parser 1
#define Debug_Ir 1


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


#endif /* AST_H_ */


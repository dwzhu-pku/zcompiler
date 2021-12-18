#ifndef AST_H_
#define AST_H_

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>

using namespace std;

#define T2R_Debug_Lex 0
#define T2R_Debug_Parser 0
#define T2R_Debug_Ir 0

extern vector<string>t2r_code_list;

class Token{
    public:
        int token_type;
        int val = 0;
        string name = "";
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

#endif /* AST_H_ */


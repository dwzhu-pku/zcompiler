#ifndef AST_H_
#define AST_H_

#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>

using namespace std;

#define E2T_Debug_Lex 0
#define E2T_Debug_Parser 0
#define E2T_Debug_Ir 0

extern vector<string>e2t_code_list;
extern vector<string>init_list;
extern vector<int>var_list;
extern map<string, int> stack_map;
extern map<string, string>global_map;
extern map<string, int> global_isarr;
extern map<string, int> stack_isarr;
extern vector<int>param_isarr;
extern int stack_idx;
extern int stack_size;
extern int param_cnt;
extern int reg_idx;
extern int in_func;

int e2t_get_next_var();

class E2T_Token{
    public:
        int token_type;
        int val = 0;
        string name = "";
        string ir_addr = "";
        string reg = "";
        int line_no = 0;

        E2T_Token(){
            ;
        }
        E2T_Token(int token_type_, int val_, int line_no_){
            token_type = token_type_;
            val = val_;
            line_no = line_no_;
        }
        E2T_Token(int token_type_, const string & name_, int line_no_){
            token_type = token_type_;
            name = name_;
            line_no = line_no_;
        }
};


#endif /* AST_H_ */


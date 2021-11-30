#ifndef SYM_H_
#define SYM_H_

#include<stack>
#include<map>
#include<string>
#include<vector>

using namespace std;

class SymItem{
    public:
        string ident_name;
        string ir_name;
        int ident_type;
        int is_fun;
        vector<int> offset_vec;

        SymItem(string ident_name_, string ir_name_, int ident_type_, int is_fun_){
            ident_name = ident_name_;
            ir_name = ir_name_;
            ident_type = ident_type_;
            is_fun = is_fun_;
        }

        SymItem(string ident_name_, string ir_name_, int ident_type_, int is_fun_, vector<int>& offset_vec_){
            ident_name = ident_name_;
            ir_name = ir_name_;
            ident_type = ident_type_;
            is_fun = is_fun_;
            for(auto i: offset_vec_){
                offset_vec.push_back(i);
            }
        }
};



#define SymTable map<string, SymItem*> 

extern SymTable fun_sym_table;

extern stack<SymTable*> var_sym_stack;


#endif /* SYM_H_ */
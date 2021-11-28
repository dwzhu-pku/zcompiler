#ifndef SYM_H_
#define SYM_H_

#include<stack>
#include<map>
#include<string>

using namespace std;

class SymItem{
    public:
        string ident_name;
        string ir_name;
        int ident_type;
        int is_fun;

        SymItem(string ident_name_, string ir_name_, int ident_type_, int is_fun_){
            ident_name = ident_name_;
            ir_name = ir_name_;
            ident_type = ident_type_;
            is_fun = is_fun_;
        }
};



#define SymTable map<string, SymItem*> 

extern SymTable fun_sym_table;

extern stack<SymTable*> var_sym_stack;


#endif /* SYM_H_ */
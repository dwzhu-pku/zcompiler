#include"ast.hpp"

vector<string>code_list;
vector<int>label_list = {-1};
vector<int>native_list = {-1};
vector<int>temp_list = {-1};
stack<BaseAst*>while_list;

string str_t = "t";
string str_T = "T";

int temp_index = 0;
int native_index = 0;
int code_index = 0;

void FunDefAst::genCode(){
    if (Debug_Ir) printf("Generating code for FunDefAst\n");

    auto item = fun_sym_table.find(name);
    if( item != fun_sym_table.end()){
        printf("Token already declared in this symbol table, Override!\n");
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
        if (para->node_type != AstType::kList){
            SymItem* tmp_ptr = new SymItem(((DeclAst*)para)->name, para->addr, ((DeclAst*)para)->var_type, 0);
            (*cur)[((DeclAst*)para)->name]=tmp_ptr;
        }else{
            ListAst* list_ptr = dynamic_cast<ListAst*>(para);
            SymItem* tmp_ptr = new SymItem(list_ptr->name, list_ptr->addr, 1, 0, list_ptr->offset_vec);
            (*cur)[list_ptr->name] = tmp_ptr;
        }
    }
    
    fun_body->genCode();

    var_sym_stack.pop();

    code_list.push_back( "end " + addr);

    return;
}
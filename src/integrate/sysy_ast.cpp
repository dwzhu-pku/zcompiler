#include"sysy_ast.hpp"

vector<string>code_list;
vector<int>label_list = {-1};
vector<int>native_list = {-1};
vector<int>temp_list = {-1};
stack<BaseAst*>while_list;


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
            list_ptr->get_dim_offset();
            SymItem* tmp_ptr = new SymItem(list_ptr->name, list_ptr->addr, 1, 0, list_ptr->offset_vec);
            (*cur)[list_ptr->name] = tmp_ptr;
        }
    }
    
    fun_body->genCode();
    var_sym_stack.pop();
    code_list.push_back( "end " + addr);

    return;
}

void FunCallAst::genCode(){
    if (Debug_Ir) printf("Generating code for FunCallAst\n");
    if(name == "starttime" || name == "stoptime") {
        // exit(-1);
        name = "_sysy_" + name;
        fun_params.push_back(new BinaryOpAst(nullptr, nullptr, "",lineno, 1));
    }
    auto item = fun_sym_table.find(name);
    if( item == fun_sym_table.end()){
        printf("Error! Function not declared in this symbol table!\n");
        return;
    }
    for (auto para: fun_params){
        para->genCode();
    }
    for (auto para: fun_params){
        code_list.push_back("param " + para->addr);
    }
    // void
    if (item->second->ident_type == 0){
        code_list.push_back("call " + item->second->ir_name );
    }else{ // int
        int tmp = temp_list.back();
        temp_list.push_back(tmp + 1);
        addr = "t" + to_string(tmp + 1);
        code_list.push_back( "var " + addr);
        code_list.push_back( addr + " = call " + item->second->ir_name );

        if(!(branch1 == "" && branch2 == "" && next == "")){
            code_list.push_back("if " + addr + " != 0 goto " + branch1);
            code_list.push_back("goto " + branch2);
        }
    }
}

void WhileAst::genCode(){
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

    code_list.push_back( branch2 + ":");

    while_stmt->genCode();
    code_list.push_back( "goto " + branch1);

    code_list.push_back( next + ":");

    while_list.pop();
}

void BreakAst::genCode(){
    if (Debug_Ir) printf("Generating code for BreakAst\n");
    next = while_list.top()->next;
    code_list.push_back( "goto "+ next);
}

void ContinueAst::genCode(){
    if (Debug_Ir) printf("Generating code for ContinueAst\n");
    next = while_list.top()->branch1;
    code_list.push_back( "goto "+ next);
}

void LvalAst::genCode(){
    if (Debug_Ir) printf("Generating code for LvalAst\n" );
    SymTable* cur = var_sym_stack.top();
    auto item = cur->find(name);
    if( item == cur->end()){
        printf("Error! Token not in this symbol table!\n");
        return;
    }
    addr = item->second->ir_name;
    vector<long long>offset_vec = item->second->offset_vec;
    
    /*此时，该引用为数组*/
    if (offset_vec.size() > 0){
        int tmp = temp_list.back();
        temp_list.push_back(tmp+1);
        temp_list.push_back(tmp+2);
        string add_tmp = "t" + to_string(tmp+1);
        string mul_tmp = "t" + to_string(tmp+2);
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
            string sum_tmp = "t" + to_string(tmp+1);
            code_list.push_back( "var " + sum_tmp);
            code_list.push_back( sum_tmp  + " = 0" );
            code_list.push_back( sum_tmp + " = " + addr + " + " + add_tmp);
            addr = sum_tmp;
        }
        if(is_left_val == 0){
            tmp = temp_list.back();
            temp_list.push_back(tmp+1);
            string var_tmp = "t" + to_string(tmp+1);
            code_list.push_back( "var " + var_tmp);
            code_list.push_back(var_tmp + " = " + addr);
            addr = var_tmp;
        }
    }
    if(!(branch1 == "" && branch2 == "" && next == "")){
        code_list.push_back("if " + addr + " != 0 goto " + branch1);
        code_list.push_back("goto " + branch2);
    }
}

void AssignAst::genCode(){
    if (Debug_Ir) printf("Generating code for AssignAst\n");
    SymTable* cur = var_sym_stack.top();
    auto item = cur->find(dynamic_cast<LvalAst*>(lval)->name);
    if( item == cur->end()){
        printf("Error! Token not in this symbol table!\n");
        return;
    }
    lval->genCode();
    exp->genCode();
    code_list.push_back(lval->addr + " = " + exp->addr);
}

void DeclAst::genCode(){
    if (Debug_Ir) printf("Generating code for DeclAst\n");
    SymTable* cur = var_sym_stack.top();
    auto item = cur->find(name);
    if( item != cur->end()){
        printf("Token already declared in this symbol table, Override!\n");
    }
    int tmp = native_list.back();
    native_list.push_back(tmp+1);
    addr = "T" + to_string(tmp+1);
    code_list.push_back( "var " + addr);

    if(is_const == 0){
        SymItem* ptr = new SymItem(name, addr, var_type, 0);
        (*cur)[name]=ptr;
        if(exp!=nullptr){
            exp->genCode();
            if(var_sym_stack.size() == 2){
                code_list.push_back(addr + " = " + to_string(exp->calVal()));
            }else{
                code_list.push_back(addr + " = " + exp->addr);
            }
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

void ArrayAst::genCode(){
    if (Debug_Ir) printf("Generating code for ArrayAst\n");
    for(auto i: array_list){
        i->is_const = is_const;
        i->genCode();
    }
}

void BlockAst::genCode(){
    if (Debug_Ir) printf("Generating code for BlockAst\n");
    SymTable* map_ptr = new SymTable();
    if(var_sym_stack.size() > 0)
        *map_ptr = *(var_sym_stack.top());
    var_sym_stack.push(map_ptr);

    for(auto i: list_stmts){
        i->genCode();
    }

    var_sym_stack.pop();
}

void IfAst::genCode(){
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

void ReturnAst::genCode(){
    if (Debug_Ir) printf("Generating code for ReturnAst\n");
    if(exp == nullptr){
        code_list.push_back( "return");
    }else{
        exp->genCode();
        code_list.push_back( "return " + exp->addr);
    }
}

void BinaryOpAst::genCode(){
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
        addr = "t" + to_string(tmp + 1);
        code_list.push_back( "var " + addr);

        code_list.push_back(addr + " = " + lt_exp->addr + " " + op + " " + rt_exp->addr);
        if(!(branch1 == "" && branch2 == "" && next == "")){
            code_list.push_back("if " + addr + " != 0 goto " + branch1);
            code_list.push_back("goto " + branch2);
        }
    }
}

void UnaryOpAst::genCode(){
    // 不在 if cond 中时的行为
    if(branch1 == "" && branch2 == "" && next == ""){
        exp->genCode();
        int tmp = temp_list.back();
        temp_list.push_back(tmp + 1);
        addr = "t" + to_string(tmp + 1);
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

void ListAst::genCode(){
    if (Debug_Ir) printf("Generating code for ListAst\n");
    SymTable* cur = var_sym_stack.top();
    auto item = cur->find(name);
    if( item != cur->end()){
        printf("Token already declared in this symbol table, Override!\n");
    }
    int tmp = native_list.back();
    native_list.push_back(tmp+1);
    addr = "T" + to_string(tmp+1);
    
    /* 数组相关计算 */
    get_dim_offset();

    /* 数组声明 */
    code_list.push_back( "var " + to_string(list_size) + " " +  addr);

    if(is_const || var_sym_stack.size() == 2){ // 常量或全局数组
        SymItem* ptr = new SymItem(name, addr, 2, 0, offset_vec);
        init_val_vec.resize(list_size/4, 0);
        get_init_val(list_inits, 0, 0);
        ptr->init_val_list = init_val_vec;
        (*cur)[name]=ptr;
    }else{
        SymItem* ptr = new SymItem(name, addr, 1, 0, offset_vec);
        (*cur)[name]=ptr;
        /* 数组初始化 */
        if(list_inits.size() > 0){
            set_init_val(list_inits, 0, 0);
        }
    }
}

int LvalAst::calVal(){
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
        long long tmp_ofs = 0;
        for(int i = 0; i < int(list_dims.size()); ++i){
            long long tmp_dim = list_dims[i]->calVal();
            tmp_ofs += tmp_dim * item->second->offset_vec[i+1];
        }
        return item->second->init_val_list[tmp_ofs];
    }else{ // 变量
        return item->second->init_val_list[0];
    }
}

int BinaryOpAst::calVal(){
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
            return tmp1 / tmp2;
        }else if (op == "%"){
            return tmp1 % tmp2;
        }else{
            return 0;
        }
    }
}

int UnaryOpAst::calVal(){
    int tmp = exp->calVal();
    if(op == "+"){
        return tmp; 
    }else if(op == "-"){
        return -tmp;
    }else{
        return 0;
    }
}



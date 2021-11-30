#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"ast.hpp"
#include"sym.hpp"
#include"parser.tab.hpp"
extern FILE * yyin;
extern FILE * yyout;

map<AstType, string> type2str={
    {AstType::kAssign, "Assign"},
    {AstType::kDecl, "Decl"},
    {AstType::kFunDef, "FunDef"},
    {AstType::kFunCall, "FunCall"},
    {AstType::kBlock, "Block"},
    {AstType::kIf, "If"},
    {AstType::kWhile, "While"},
    {AstType::kBreak, "Break"},
    {AstType::kContinue, "Continue"},
    {AstType::kReturn, "Return"},
    {AstType::kBinaryOp, "BinaryOp"},
    {AstType::kUnaryOp, "UnaryOp"},
    {AstType::kBase, "Base"},
    {AstType::kArray, "Array"},
    {AstType::kLval, "Lval"},
    {AstType::kList, "List"},
};

map<int, string> int2type={
    {1, "Int"},
    {0, "Void"},
};

// map<int, string> int2op={
//     {ADD, "+"},
//     {SUB, "-"},
//     {MUL, "*"},
//     {DIV, "/"},
//     {MOD, "%"},
//     {NOT, "!"},

//     {LT, "<"},
//     {GT, ">"},
//     {LE, "<="},
//     {GE, ">="},
//     {EQ, "=="},
//     {NE, "!="},

//     {LAND, "&&"},
//     {LOR, "||"},
// };

void dfsAst(BaseAst* ptr, int level){
    string prefix;
    for(int i=0;i < level;++i){
        prefix += "\t";
    }

    if(ptr == nullptr){
        printf("%sLeaf Node reached\n", prefix.c_str());
        return;
    }

    printf("%sNode type: %s\n", prefix.c_str(), type2str[ptr->node_type].c_str());

    if(ptr->node_type == AstType::kAssign){
        AssignAst * new_ptr =  dynamic_cast<AssignAst*>(ptr);
        dfsAst(new_ptr->lval, level+1);
        dfsAst(new_ptr->exp, level+1);
    }

    if(ptr->node_type == AstType::kDecl){
        DeclAst * new_ptr =  dynamic_cast<DeclAst*>(ptr);
        printf("%sLeft Value name: %s, Value type is: %s\n", prefix.c_str(), new_ptr->name.c_str(), int2type[new_ptr->var_type].c_str());
        dfsAst(new_ptr->exp, level+1);
    }

    if(ptr->node_type == AstType::kLval){
        LvalAst * new_ptr =  dynamic_cast<LvalAst*>(ptr);
        printf("%sLeft Value name: %s\n", prefix.c_str(), new_ptr->name.c_str());
        if (new_ptr->list_dims.size() > 0){
            for(auto i: new_ptr->list_dims){
                dfsAst(i, level+1);
            }
        }
    }

    if(ptr->node_type == AstType::kFunDef){
        FunDefAst * new_ptr =  dynamic_cast<FunDefAst*>(ptr);
        printf("%sFunction Define, name: %s, Value type is: %s\n", prefix.c_str(), new_ptr->name.c_str(), int2type[new_ptr->var_type].c_str());
        dfsAst(new_ptr->fun_body, level+1);
        for(auto para: new_ptr->fun_params){
            dfsAst(para, level+1);
        }
    }

    if(ptr->node_type == AstType::kFunCall){
        FunCallAst * new_ptr =  dynamic_cast<FunCallAst*>(ptr);
        printf("%sFunction Call, name: %s\n", prefix.c_str(), new_ptr->name.c_str());
        for(auto para: new_ptr->fun_params){
            dfsAst(para, level+1);
        }
    }

    if(ptr->node_type == AstType::kArray){
        ArrayAst * new_ptr =  dynamic_cast<ArrayAst*>(ptr);
        for(auto para: new_ptr->array_list){
            dfsAst(para, level+1);
        }
    }

    if(ptr->node_type == AstType::kBlock){
        BlockAst * new_ptr =  dynamic_cast<BlockAst*>(ptr);
        for(auto stmt: new_ptr->list_stmts){
            dfsAst(stmt, level+1);
        }
    }

    if(ptr->node_type == AstType::kIf){
        IfAst * new_ptr =  dynamic_cast<IfAst*>(ptr);
        dfsAst(new_ptr->if_cond, level+1);
        dfsAst(new_ptr->if_then_stmt, level+1);
        dfsAst(new_ptr->else_stmt, level+1);
    }

    if(ptr->node_type == AstType::kWhile){
        WhileAst * new_ptr =  dynamic_cast<WhileAst*>(ptr);
        dfsAst(new_ptr->while_cond, level+1);
        dfsAst(new_ptr->while_stmt, level+1);
    }

    if(ptr->node_type == AstType::kBreak){
    }

    if(ptr->node_type == AstType::kContinue){
    }

    if(ptr->node_type == AstType::kReturn){
        ReturnAst * new_ptr =  dynamic_cast<ReturnAst*>(ptr);
        dfsAst(new_ptr->exp, level+1);
    }

    if(ptr->node_type == AstType::kBinaryOp){
        BinaryOpAst * new_ptr =  dynamic_cast<BinaryOpAst*>(ptr);
        if(new_ptr->is_const){
            printf("%sConst value is %d\n", prefix.c_str(), new_ptr->val);
        }else{
            printf("%sOp is: %s\n", prefix.c_str(), new_ptr->op.c_str());
        }
        dfsAst(new_ptr->lt_exp, level+1);
        dfsAst(new_ptr->rt_exp, level+1);
    }

    if(ptr->node_type == AstType::kUnaryOp){
        UnaryOpAst * new_ptr =  dynamic_cast<UnaryOpAst*>(ptr);
        printf("%sOp is: %s\n", prefix.c_str(), new_ptr->op.c_str());
        dfsAst(new_ptr->exp, level+1);
    }

    if(ptr->node_type == AstType::kList){
        ListAst * new_ptr =  dynamic_cast<ListAst*>(ptr);
        printf("%sArray name is: %s\n", prefix.c_str(), new_ptr->name.c_str());
        printf("%sdims:\n", prefix.c_str());
        for(auto stmt: new_ptr->list_dims){
            dfsAst(stmt, level+1);
        }
        printf("%sinit stmts:\n", prefix.c_str());
        for(auto stmt: new_ptr->list_inits){
            dfsAst(stmt, level+1);
        }
    }

    return;
}

void getRuntimeFun(){
    SymItem* ptr = new SymItem("getint", "f_getint", 1, 1);
    fun_sym_table.insert(make_pair("getint", ptr));
    
    ptr = new SymItem("getch", "f_getch", 1, 1);
    fun_sym_table.insert(make_pair("getch", ptr));

    ptr = new SymItem("putint", "f_putint", 0, 1);
    fun_sym_table.insert(make_pair("putint", ptr));

    ptr = new SymItem("putch", "f_putch", 0, 1);
    fun_sym_table.insert(make_pair("putch", ptr));

    ptr = new SymItem("getarray", "f_getarray", 1, 1);
    fun_sym_table.insert(make_pair("getarray", ptr));

    ptr = new SymItem("putarray", "f_putarray", 0, 1);
    fun_sym_table.insert(make_pair("putarray", ptr));
}

void reorderCode(){
    stack<int> st_mark;
    st_mark.push(0);
    int list_size = code_list.size();

    for(int i = 0; i < list_size; ++i){
        auto it = code_list.begin() + i;
        if (it->size() > 2 && it->compare(0,2,"f_") == 0){
            st_mark.push(i+1);
            
        }
        else if (it->size() > 3 && it->compare(0,3,"end") == 0){
            st_mark.pop();
        }

        else if (it->size() > 3 && it->compare(0,3,"var") == 0){
            rotate(code_list.begin() + st_mark.top(), it, it + 1);
        }

    }
}

int main(int argc, char **argv){

    if (argc < 2) {
        cout<<"Parameter Error!"<<endl;
        return 1;
    }

    char opt;
    char *input_path = nullptr;
    char *output_path = nullptr;
    while( (opt = getopt(argc, argv, "e:o:S")) != -1 ){
            if(opt == 'e') input_path = optarg;
            if(opt == 'o') output_path = optarg;
    }

    FILE* input = fopen(input_path, "r");
    if(input == nullptr){
        cout<<"Error, no input file!"<<endl;
        return 1;
    } 
    FILE* output = fopen(output_path, "w");
    if(output == nullptr){
        cout<<"Error, no output file!"<<endl;
        return 1;
    }
    yyin = input;
    yyout = output;

    streambuf* bak_cout = cout.rdbuf();
    ofstream new_cout(output_path);
    cout.rdbuf(new_cout.rdbuf());

    getRuntimeFun();
    BaseAst* root;
    yyparse(&root);
    // dfsAst(root, 0);
    var_sym_stack.push(new SymTable());
    root->genCode();
    reorderCode();
    for(string line: code_list){
        cout<<line<<endl;
    }


    //恢复cout重定向
    cout.rdbuf(bak_cout);

    fclose(input);
    fclose(output);
    return 0;
}
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"tigger_ast.hpp"
#include"tigger_parser.tab.hpp"
extern FILE * t2r_yyin;
extern FILE * t2r_yyout;

int tigger2riscv(FILE * f_yyin, FILE* f_yyout, char* output_path){

    if(f_yyin == nullptr){
        cout<<"Error, no input file!"<<endl;
        return 1;
    } 
    if(f_yyout == nullptr){
        cout<<"Error, no output file!"<<endl;
        return 1;
    }
    t2r_yyin = f_yyin;
    t2r_yyout = f_yyout;

    streambuf* bak_cout = cout.rdbuf();
    ofstream new_cout(output_path);
    cout.rdbuf(new_cout.rdbuf());

    t2r_yyparse();

    for(string line: t2r_code_list){
        cout << line << endl;
    }

    //恢复cout重定向
    cout.rdbuf(bak_cout);
    fclose(f_yyin);
    fclose(f_yyout);


    return 0;
}
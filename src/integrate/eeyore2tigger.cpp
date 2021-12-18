#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"eeyore_ast.hpp"
#include"eeyore_parser.tab.hpp"
extern FILE * e2t_yyin;
extern FILE * e2t_yyout;

int eeyore2tigger(FILE * f_yyin, FILE* f_yyout, char* output_path){

    if(f_yyin == nullptr){
        cout<<"Error, no input file!"<<endl;
        return 1;
    } 
    if(f_yyout == nullptr){
        cout<<"Error, no output file!"<<endl;
        return 1;
    }
    e2t_yyin = f_yyin;
    e2t_yyout = f_yyout;

    streambuf* bak_cout = cout.rdbuf();
    ofstream new_cout("output.tigger");
    cout.rdbuf(new_cout.rdbuf());

    e2t_yyparse();

    for(string line: e2t_code_list){
        if(line.size() >= 6 && line.compare(0,6,"f_main") == 0){
            cout<<line<<endl;
            for (string i: init_list){
                cout << i << endl;
            }
        }else{
            cout << line << endl;
        }
    }

    //恢复cout重定向
    cout.rdbuf(bak_cout);
    fclose(f_yyin);
    fclose(f_yyout);

    return 0;
}
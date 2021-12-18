#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"tigger_ast.hpp"
#include"tigger_parser.tab.hpp"
extern FILE * t2r_yyin;
extern FILE * t2r_yyout;

int main(int argc, char **argv){

    if (argc < 2) {
        cout<<"Parameter Error!"<<endl;
        return 1;
    }

    char opt;
    char *input_path = nullptr;
    char *output_path = nullptr;
    while( (opt = getopt(argc, argv, "o:S:")) != -1 ){
            if(opt == 'S'){
                input_path = optarg;
            }
            if(opt == 'o'){
                output_path = optarg;
            }
    }

    FILE* input = fopen(input_path, "r");
    if(input == nullptr){
        cout<<"Error, open input file failed!"<<endl;
        return 1;
    } 
    FILE* output = fopen(output_path, "w");
    if(output == nullptr){
        cout<<"Error, open output file failed!"<<endl;
        return 1;
    }
    t2r_yyin = input;
    t2r_yyout = output;

    streambuf* bak_cout = cout.rdbuf();
    ofstream new_cout(output_path);
    cout.rdbuf(new_cout.rdbuf());

    t2r_yyparse();

    for(string line: t2r_code_list){
        cout << line << endl;
    }

    //恢复cout重定向
    cout.rdbuf(bak_cout);
    fclose(input);
    fclose(output);


    return 0;
}
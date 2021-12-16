#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"tigger_ast.hpp"
#include"tigger_parser.tab.hpp"
extern FILE * yyin;
extern FILE * yyout;
extern int yylex();

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

    yyparse();

    for(string line: code_list){
        cout << line << endl;
    }

    //恢复cout重定向
    cout.rdbuf(bak_cout);
    fclose(input);
    fclose(output);


    return 0;
}
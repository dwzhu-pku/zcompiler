#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>
#include<algorithm>
#include"eeyore_ast.hpp"
#include"eeyore_parser.tab.hpp"
extern FILE * e2t_yyin;
extern FILE * e2t_yyout;

int main(int argc, char **argv){

    if (argc < 2) {
        cout<<"Parameter Error!"<<endl;
        return 1;
    }

    char opt;
    char *input_path = nullptr;
    char *output_path = nullptr;
    while( (opt = getopt(argc, argv, "t:o:S")) != -1 ){
            if(opt == 't'){
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
    e2t_yyin = input;
    e2t_yyout = output;

    streambuf* bak_cout = cout.rdbuf();
    ofstream new_cout(output_path);
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
    fclose(input);
    fclose(output);

    return 0;
}
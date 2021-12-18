#include"eeyore_ast.hpp"
#include<string>
#include<algorithm>
#include<vector>

using namespace std;



void temp(){
    
    stack_map.clear();
    for (auto it = code_list.rbegin(); it != code_list.rend(); ++it){
        if(it->compare(0,2,"f_") == 0){
            *it = *it + "[" + to_string(stack_size) + "]";
            break;
        }
    }

}
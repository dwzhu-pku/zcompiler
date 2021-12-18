#include"eeyore_ast.hpp"
#include<string>
#include<algorithm>
#include<vector>

using namespace std;

vector<string>e2t_code_list;
vector<string>init_list;
vector<int>var_list={-1};
vector<int>param_isarr={0,0,0,0,0,0,0,0};
map<string, string>global_map;
map<string, int> stack_map;
map<string, int> global_isarr;
map<string, int> stack_isarr;


int e2t_get_next_var(){
    int tmp = var_list.back();
    var_list.push_back(tmp+1);
    return tmp+1;
}

int stack_idx = 0;
int stack_size = 0;
int param_cnt = 0;
int reg_idx = 1;
int in_func=0;


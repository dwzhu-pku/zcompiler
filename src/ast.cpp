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

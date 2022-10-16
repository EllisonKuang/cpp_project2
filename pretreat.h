#pragma once
#include <string.h>
#include <unordered_map>
using namespace std;
short expression_type(string expression);
unordered_map<string,string> InsertParam(string expression,unordered_map<string,string> ParamMap);
string substitution(string expression,unordered_map<string,string> map);

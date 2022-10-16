#pragma once
#include <string.h>
#include "utils.h"
#include <queue>
using namespace std;
short TypeCheck(string input);
norm_number normalization(string input,short type);
string int_mul(string a,string b);
norm_number mul(string a,short type_a,string b,short type_b);
int print(norm_number output,string a,string b,short type_a,short type_b);
int calculate(string expression);
int calculate_postfix(queue<string> postfix);


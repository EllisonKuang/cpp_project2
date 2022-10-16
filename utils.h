#pragma once
#include <string.h>
#include <queue>
#include <unordered_map>
using namespace std;
struct norm_number//Digital storage format
{
    bool sign;
    long long int number;
    long long int point_pos;
};
int print(norm_number output,string a,string b,short type_a,short type_b);
queue<string> in2post(queue<string> infix);
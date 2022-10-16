#include <iostream>
#include <regex>
#include <unordered_map>
#include "pretreat.h"
#include <string.h>
using namespace std;


short expression_type(string expression)
{
    regex assign("[A-Za-z]=[-]?[0-9]+([.][0-9]+)?");
    if (regex_match(expression,assign))
        return 0;
    else
        return 1;
}

unordered_map<string,string> InsertParam(string expression,unordered_map<string,string> ParamMap)
{
    string param;
    param= expression[0];
    string value = expression.substr(2,expression.length());
    ParamMap.insert(make_pair(param,value));
    return ParamMap;
}

string substitution(string expression,unordered_map<string,string> map)
{
    string x;
    unordered_map<string,string>::iterator it;
    for(int i=0;i<expression.length();i++)
    {
        x=expression[i];
        if(map.find(x)!=map.end())
            expression.replace(i,1,map.find(x)->second);
    }
    if(expression.find("sqrt")<expression.length())
    	expression.replace(expression.find("sqrt"),4,"!");
    if(expression.find("sin")<expression.length())
    	expression.replace(expression.find("sin"),3,"@");
    if(expression.find("cos")<expression.length())
    	expression.replace(expression.find("cos"),3,"#");
    return expression;
}

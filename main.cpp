#include <iostream>
#include "calculator.h"
#include "calculator.cpp"
#include "pretreat.h"
#include "pretreat.cpp"
using namespace std;

int main()
{
    cout<<"Welcome to use the calculator,if you want to quit, please enter 'quit'!"<<endl;
    string expression;
    unordered_map<string,string> ParamMap;
    while(getline(cin,expression))
    {
        if(expression=="quit")
            break;
        if(expression_type(expression)==0) //0 is assign and 1 is caculation
        {
            ParamMap = InsertParam(expression,ParamMap);
        }
        else
        {
            expression = substitution(expression,ParamMap);
            calculate(expression);
        }
    }
    cout<<"You have exited successfully."<<endl;
    return 0;
}
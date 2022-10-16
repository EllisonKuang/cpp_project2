#include <iostream>
#include <regex>
#include <unordered_map>
#include "utils.h"
#include <queue>
#include <stack>
#include <string.h>
using namespace std;

int prior(char p)
{
    if(p=='(')
        return -1;
    if(p=='+'||p=='-')
        return 0;
    if(p=='!'||p=='@'||p=='#')
        return 2;
    return 1;
}
queue<string> in2post(string expression)
{
    queue<string> infix;
    string temp;
    stack<char> st;
    for(const auto &pointer:expression)
    {
        if((pointer=='+'||pointer=='-'||pointer=='*'||pointer=='/'||pointer==')'||pointer=='!'||pointer=='@'||pointer=='#')&&(temp!=""))
        {
            infix.push(temp);
            temp="";
        }
        if(pointer=='+'||pointer=='-'||pointer=='*'||pointer=='/'||pointer=='!'||pointer=='@'||pointer=='#')
        {
            while((!st.empty())&&(prior(pointer)<=prior(st.top())))
            {
                string t;
                t=st.top();
                infix.push(t);
                st.pop();
            }
            st.push(pointer);
        }
        else if(pointer=='(')
        {
            st.push(pointer);
        }
        else if(pointer==')')
        {
            while (st.top()!='(')
            {
                string t;
                t=st.top();
                infix.push(t);
                st.pop();
            }
            st.pop();
        }
        else
            temp+=pointer;
    }
    if(temp!="")
    {
        infix.push(temp);
    }
    while(!st.empty())
    {
        string t;
        t=st.top();
        infix.push(t);
        st.pop();
    }
    return infix;
}


int print(norm_number output,string a,string b,short type_a,short type_b)//Convert standard format data to output format data
{
    string result = "";
    if(output.number==0)
        cout<<"0"<<endl;
    else
    {
        if(output.sign)
            cout<<"-";
        short type = 0;
        if(type_a>=type_b)
            type=type_a;
        else
            type=type_b;
        if(type<=2||output.point_pos==0)
        {
            cout<<std::to_string(output.number);
            for(int i=0;i<output.point_pos;i++)
                cout<<"0";
            cout<<endl;
        }
        else if (type<=4)
        {
            long long int len = std::to_string(output.number).length();
            if(len+output.point_pos>0)
                for(int i=0;i<len;i++)
                {
                    cout<<std::to_string(output.number)[i];
                    if(i==len+output.point_pos-1)
                        cout<<".";
                }
            else
            {
                for(int i=0;i<-output.point_pos;i++)
                {
                    if(i<=-output.point_pos-len)
                        cout<<"0";
                    if(i==0)
                        cout<<".";
                    if(i>=-output.point_pos-len)
                        cout<<std::to_string(output.number)[i+len+output.point_pos];
                }
            }
            cout<<endl;
        }
        else
        {
            long long int len = std::to_string(output.number).length();
            for(int i=0;i<len;i++)
            {
                cout<<std::to_string(output.number)[i];
                if(i==0&&len>1)
                    cout<<".";
            }
            cout<<"e"<<output.point_pos+len-1<<endl;
        }
    }
    return 0;
}

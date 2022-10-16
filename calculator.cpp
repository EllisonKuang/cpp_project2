#include <iostream>
#include <regex>
#include <cmath>
#include <queue>
#include <string.h>
#include "utils.h"
#include "calculator.h"
#include "utils.cpp"
using namespace std;

short TypeCheck(string input)//Detect input type
{
    regex positive_integer("[+]?[0-9]+");
    regex negative_integer("^-[0-9]+");
    regex positive_decimal("[+]?[0-9]+[.][0-9]+");
    regex negative_decimal("^-[0-9]+[.][0-9]+");
    if (regex_match(input,positive_integer))
        return 1;
    else if (regex_match(input,negative_integer))
        return 2;
    else if (regex_match(input,positive_decimal))
        return 3;
    else if (regex_match(input,negative_decimal))
        return 4;
    return 0;
}
norm_number normalization(string input,short type)//Converts input data to a standard format
{
    norm_number result;
    if((type==1)||(type==3)||(type==5))
        result.sign = 0;
    else
    {
        result.sign = 1;
        input.erase(0,1);
    }
    if(input[0]=='+')
    {
        input.erase(0,1);
    }
    if((type==1)||(type==2))
    {
        result.number = atoi(input.c_str());
        result.point_pos = 0;
    }
    if((type==3)||(type==4))
    {
        string::iterator point;
        long long int len = input.length(),i=0;
        for (point = input.begin();point!=input.end();point++)
        {
            i+=1;
            if(*point=='.')
            {
                input.erase(point);
                break;
            }
        }
        result.number = atoi(input.c_str());;
        result.point_pos = i-len;
    }
    return result;
}

norm_number mul(string a,short type_a,string b,short type_b)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number norm_b = normalization(b,type_b);
    norm_number result;
    result.number = norm_a.number*norm_b.number;
    result.point_pos = norm_a.point_pos+norm_b.point_pos;
    result.sign = norm_a.sign ^ norm_b.sign;
    return result;
}

norm_number div(string a,short type_a,string b,short type_b)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number norm_b = normalization(b,type_b);
    norm_number result;
    result.number = norm_a.number/norm_b.number;
    result.point_pos = norm_a.point_pos-norm_b.point_pos;
    result.sign = norm_a.sign ^ norm_b.sign;
    return result;
}

norm_number add(string a,short type_a,string b,short type_b)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number norm_b = normalization(b,type_b);
    norm_number result;
    if(norm_a.point_pos>norm_b.point_pos)
    {
        norm_a.number = norm_a.number*10^(norm_a.point_pos-norm_b.point_pos);
        norm_a.point_pos=norm_b.point_pos;
    }
    else if(norm_a.point_pos<norm_b.point_pos)
    {
        norm_b.number = norm_b.number*10^(norm_b.point_pos-norm_a.point_pos);
        norm_b.point_pos=norm_a.point_pos;
    }
    result.number = norm_a.number+norm_b.number;
    result.point_pos = norm_b.point_pos;
    result.sign = norm_b.sign;
    return result;
}

norm_number minu(string a,short type_a,string b,short type_b)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number norm_b = normalization(b,type_b);
    norm_number result;
    if(norm_a.point_pos>norm_b.point_pos)
    {
        norm_a.number = norm_a.number*10^(norm_a.point_pos-norm_b.point_pos);
        norm_a.point_pos=norm_b.point_pos;
    }
    else if(norm_a.point_pos<norm_b.point_pos)
    {
        norm_b.number = norm_b.number*10^(norm_b.point_pos-norm_a.point_pos);
        norm_b.point_pos=norm_a.point_pos;
    }
    if(norm_a.number>norm_b.number)
    {
        result.number = norm_a.number-norm_b.number;
        result.point_pos = norm_b.point_pos;
        result.sign = norm_b.sign;
    }
    else
    {
        result.number = norm_b.number-norm_a.number;
        result.point_pos = norm_b.point_pos;
        result.sign = !norm_b.sign;
    }
    
    return result;
}

norm_number sqrts(string a,short type_a)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number result;
        result.number = sqrt(norm_a.number);
        result.point_pos = norm_a.point_pos/2;
        result.sign = norm_a.sign;
    return result;
}

norm_number sins(string a,short type_a)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number result;
        result.number = 100*sin(3.1415926*norm_a.number/180);
        result.point_pos = -2;
        result.sign = norm_a.sign;
    return result;
}

norm_number coss(string a,short type_a)//Multiply the input data
{
    norm_number norm_a = normalization(a,type_a);
    norm_number result;
        result.number = 100*cos(3.1415926*norm_a.number/180);
        result.point_pos = -2;
        result.sign = norm_a.sign;
    return result;
}


int calculate(string expression)
{
    queue<string> postfix=in2post(expression);
    calculate_postfix(postfix);
    return 0;
}


string back_norm(norm_number output,string a,string b,short type_a,short type_b)//Convert standard format data to output format data
{
    string result = "";
    if(output.number==0)
        return "0";
    else
    {
        if(output.sign)
            result+="-";
        short type = 0;
        if(type_a>=type_b)
            type=type_a;
        else
            type=type_b;
        if(type<=2||output.point_pos==0)
        {
            result+=std::to_string(output.number);
            for(int i=0;i<output.point_pos;i++)
                result+="0";
        }
        else if (type<=4)
        {
            long long int len = std::to_string(output.number).length();
            if(len+output.point_pos>0)
                for(int i=0;i<len;i++)
                {
                    result+=std::to_string(output.number)[i];
                    if(i==len+output.point_pos-1)
                        result+=".";
                }
            else
            {
                for(int i=0;i<-output.point_pos;i++)
                {
                    if(i<=-output.point_pos-len)
                        result+="0";
                    if(i==0)
                        result+=".";
                    if(i>=-output.point_pos-len)
                        result+=std::to_string(output.number)[i+len+output.point_pos];
                }
            }
        }
    }
    return result;
}

string cal(string value1,string value2,string element)
{
    short type_a = TypeCheck(value1),type_b = TypeCheck(value2);
    norm_number result;
    if(element=="*")
        result = mul(value1,type_a,value2,type_b);
    if(element=="/")
        result = div(value2,type_a,value1,type_b);
    if(element=="+")
        result = add(value1,type_a,value2,type_b);
    if(element=="-")
        result = minu(value2,type_a,value1,type_b);
    return back_norm(result,value1,value2,type_a,type_b);
}

string cal2(string value1,string element)
{
    short type_a = TypeCheck(value1);
    norm_number result;
    if(element=="!")
        result = sqrts(value1,type_a);
    if(element=="@")
        result = sins(value1,type_a);    
    if(element=="#")
        result = coss(value1,type_a);
    return back_norm(result,value1,value1,3,3);
}

int calculate_postfix(queue<string> postfix)
{
    string element;
    string value1,value2;
    stack<string> st;
    while(!postfix.empty())
    {
        element = postfix.front();
        postfix.pop();
        if(element=="+"||element=="-"||element=="*"||element=="/")
        {
            value1=st.top();
            st.pop();
            value2=st.top();
            st.pop();
            string tempresult = cal(value1,value2,element);
            st.push(tempresult);
        }
        else if(element=="!"||element=="@"||element=="#")
        {
            value1=st.top();
            st.pop();
            string tempresult = cal2(value1,element);
            st.push(tempresult);
        }
        else
            st.push(element);
    }
    cout<<st.top()<<endl;
    return 0;
}

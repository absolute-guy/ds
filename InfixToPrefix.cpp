#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
using namespace std;

int Precedence(char op){
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    return 0;
}

string InfixToPostfix(string exp){
    stack<char> st;
    string result="";
    
    for(int i=0;i<exp.length();i++){
        char c=exp[i];

    if(isalnum(c)){
        result+=c;
    }

    else if (c == '('){
        st.push(c);
    }

    else if(c == ')'){
        while(!st.empty() && st.top() != '('){
            result+=st.top();
            st.pop();
        }
        st.pop();
    }

    else{
        while(!st.empty() && Precedence(st.top())>= Precedence(c)){
            result+=st.top();
            st.pop();
        }
        st.push(c);
    }
   }
   while(!st.empty()){
    result+=st.top();
    st.pop();
   } 
   return result;
}

string InfixToPrefix(string exp){
    reverse(exp.begin(), exp.end());

    
    for(int i=0;i<exp.length();i++){
        if(exp[i] == '(') exp[i] = ')';
        else if(exp[i] == ')') exp[i] = '(';
    }

    string postfix = InfixToPostfix(exp);
    reverse(postfix.begin(), postfix.end());

    return postfix;
}

int main()
{
    string exp="A+B*C";
    cout<<InfixToPrefix(exp);
}
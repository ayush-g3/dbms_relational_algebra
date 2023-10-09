#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include <bits/stdc++.h>
using namespace std;

string infix_to_postfix_logical_operators_only(string bool_exp){
    stack<char> st;
    
    string postfix;
    for(int i=0; i<bool_exp.size(); i++){
        if(bool_exp[i]=='0' || bool_exp[i]=='1'){
            postfix.push_back(bool_exp[i]);
        }
        else if(bool_exp[i]=='('){
            st.push('(');
        }
        else if(bool_exp[i]==')'){
            while(st.top()!='('){
                postfix.push_back(st.top());
                st.pop();
            }
            st.pop();
        }
        else{
            if(st.size()==0 || st.top()=='('){
                st.push(bool_exp[i]);
                continue;
            } 
            
            if(st.top()>bool_exp[i]){
                st.push(bool_exp[i]);
            }
            else{
                while(st.size()>0 && st.top()<bool_exp[i]){
                    postfix.push_back(st.top());
                    st.pop();
                }
                if(st.size()>0 && st.top()==bool_exp[i]){
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(bool_exp[i]);
            }
        }
    }
    while(st.size()>0){
        postfix.push_back(st.top());
        st.pop();
    }
    
    return postfix;
}

bool evaluate_logical_operatos_only(string postfix){
    stack<bool> st;
    
    for(int i=0; i<postfix.size(); i++){
        if(postfix[i]=='&'){
            bool a=st.top(); st.pop();
            bool b=st.top(); st.pop();
            
            st.push(a&b);
        }
        else if(postfix[i]=='|'){
            bool a=st.top(); st.pop();
            bool b=st.top(); st.pop();
            
            st.push(a|b);
        }
        else if(postfix[i]=='!'){
            bool a=st.top(); st.pop();
            
            st.push(!a);
        }
        else if(postfix[i]=='0' || postfix[i]=='1'){
            st.push(postfix[i]-'0');
        }
        else{
            cout << "error" ;
            exit(0);
        }
    }
    
    return st.top();
}

#endif
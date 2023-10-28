#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include <bits/stdc++.h>

using namespace std;

bool isOperand(char s){
    if((s>='a' && s<='z') || (s>='A' && s<='Z') || (s>='0' && s<='9')){
        return 1;
    }
    return 0;
}

vector<string> infix_to_postfix(string command){
    map<char, int> precedence;
    precedence['$']=3;
    precedence['#']=3;
    precedence['%']=3;
    precedence['~']=2;
    precedence['*']=2;
    precedence['@']=2;
    precedence['/']=2;
    precedence['^']=1;
    precedence['+']=0;
    precedence['-']=0;
    
    vector<string> postfix;
    stack<string> st;
    for(int i=0; i<command.size(); i++){
        if(command[i]==' ') continue;
        else if(isOperand(command[i])){
            string operand;
            int j=i;
            while(j<command.size() && isOperand(command[j])){
                operand.push_back(command[j]);
                j++;
            }
            
            // cout << "operand: " << operand << endl;
            
            postfix.push_back(operand);
            i=j-1;
        }
        else if(command[i]=='('){
            st.push("(");
        }
        else if(command[i]==')'){
            while(st.size()>0 && st.top()!="("){
                postfix.push_back(st.top()); st.pop();
            }
            st.pop();
        }
        else{
            
            // extract the operator from command, 
            // here the operator can be of length more than 1 also eg. $[]
            string op; op.push_back(command[i]);
            if(op=="*" && command[i+1]=='~'){
                i++;
                op.push_back(command[i]);
            }
            if(op=="~"){
                i++;
                if(command[i]!='*'){
                    cout << "Invalid operator!" << endl;
                    exit(0);
                }
                op.push_back(command[i]);
            }
            int j=i+1;
            while(j<command.size() && command[j]==' ') j++;
            if(j<command.size() && command[j]=='['){
                while(j<command.size() && command[j]!=']'){
                    op.push_back(command[j]);
                    j++;
                }
                op.push_back(']'); j++;
            }
            i=j-1;
            
            // cout << "op: " << op << endl;
            
            if(st.size()==0 || st.top()=="("){
                st.push(op);
                continue;
            }
            
            if(precedence[op[0]] > precedence[st.top()[0]]){
                st.push(op);
            }
            else if(precedence[op[0]] < precedence[st.top()[0]]){
                while(st.size()>0 && precedence[op[0]] < precedence[st.top()[0]]){
                    postfix.push_back(st.top());
                    st.pop();
                }
                if(st.size()>0 && precedence[op[0]] == precedence[st.top()[0]]){
                    postfix.push_back(st.top());
                    st.pop();
                }
                st.push(op);
            }
            else{
                // for a+b+c
                postfix.push_back(st.top()); st.pop();
                st.push(op);
                // same precedence operators without parenthesis
            }
        }
    }
    
    while(st.size()>0){
        postfix.push_back(st.top()); st.pop();
    }
    
    return postfix;
}

#endif
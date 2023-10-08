#ifndef CONDITION_CHECKING_H
#define CONDITION_CHECKING_H

#include <bits/stdc++.h>
#include "table_data_structure.h"

using namespace std;

string infix_to_postfix_for_boolean(string bool_exp){
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

bool evaluate_boolean_expression(string bool_exp){
    string postfix=infix_to_postfix_for_boolean(bool_exp);
    
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

bool compare_lhs_rhs(string lhs, string comp, string rhs){
    // cout << "check_condition " << lhs << " " << comp << " " << rhs << endl;
    if(comp=="="){
        return lhs==rhs;
    }
    else if(comp=="!="){
        return lhs!=rhs;
    }
    else if(comp=="<"){
        return stoi(lhs)<stoi(rhs);
    }
    else if(comp=="<="){
        return stoi(lhs)<=stoi(rhs);
    }
    else if(comp==">"){
        return stoi(lhs)>stoi(rhs);
    }
    else if(comp==">="){
        return stoi(lhs)>=stoi(rhs);
    }
    else{
        cout << "error" ;
        exit(0);
    }
}

bool does_satisfy_cond(string cond, Table* table, int kth_row){
    string bool_exp;
    for(int i=0; i<cond.size(); i++){
        if(cond[i]=='=' || cond[i]=='<' || cond[i]=='>' || cond[i]=='!'){
            string lhs;
            int j;
            for(j=i-1; j>=0; j--){
                if(cond[j]==' ' || cond[j]=='(' || cond[j]=='&' || cond[j]=='|' || cond[j]=='!'){
                    break;
                }
                lhs.push_back(cond[j]);
            }
            
            reverse(lhs.begin(), lhs.end());
            
            string comp;
            comp.push_back(cond[i]);
            j=i+1;
            if(cond[j]=='='){
                comp.push_back(cond[j]);
                j++;
            }
            
            string rhs;
            bool quotes=0;
            for(; j<cond.size(); j++){
                if(quotes==0 && (cond[j]==' ' || cond[j]==')' || cond[j]=='&' || cond[j]=='|' || cond[j]=='!')){
                    break;
                }
                
                // in the condition always give string/char in double quotes
                if(cond[j]=='"'){
                    quotes^=1;
                }
                else rhs.push_back(cond[j]);
            }
            
            // get the index of the attribute(lhs)
            int attribute_idx=0;
            for(int x=0; x<(table->attributes).size(); x++){
                if((table->attributes)[x]==lhs){
                    attribute_idx=x; break;
                }
            }
            bool_exp.push_back('0'+compare_lhs_rhs((table->data)[kth_row][attribute_idx], comp, rhs));
            
            // cout << attribute_idx << " " << lhs << " " << op << " " << rhs << endl;
            
            // bool_exp.push_back('0'+compare_lhs_rhs((table->data)[kth_row][(table->attribute_idx)[lhs]], comp, rhs));
        }
        else if(cond[i]=='(' || cond[i]==')'){
            bool_exp.push_back(cond[i]);
        }
        else if(cond[i]=='&' || cond[i]=='|' || cond[i]=='!'){
            // both && and & will work as logical AND condition
            if(bool_exp.back()!=cond[i]){
                bool_exp.push_back(cond[i]);
            }
        }
    }
    
    bool res=evaluate_boolean_expression(bool_exp);
    
    return res;
}

#endif
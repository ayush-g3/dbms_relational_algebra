#include <bits/stdc++.h>
#include <fstream>
#include "expression.h"
using namespace std;

vector<string> row_to_vector(string &row){
    string tmp;
    vector<string> extracted_row;
    for(auto &x: row){
        if(x==','){
            extracted_row.push_back(tmp);
            tmp.clear();
            continue;
        }
        tmp.push_back(x);
    }
    extracted_row.push_back(tmp);
    return extracted_row;
}

void process_file(string file_name, vector<vector<string>> &table, unordered_map<string, int> &attribute_idx){
    ifstream file;
    string line;
    
    file.open(file_name);
    
    // processing the row of the attributes
    getline(file, line);
    vector<string> attributes = row_to_vector(line);
    for(int i=0; i<attributes.size(); i++){
        attribute_idx[attributes[i]]=i;
    }
    
    // processing other rows
    while(getline(file, line)){
        table.push_back(row_to_vector(line));
    }
    
    file.close();
}

bool check_condition(string lhs, string op, string rhs){
    // cout << "check_condition " << lhs << " " << op << " " << rhs << endl;
    if(op=="="){
        return lhs==rhs;
    }
    else if(op=="!="){
        return lhs!=rhs;
    }
    else if(op=="<"){
        return stoi(lhs)<stoi(rhs);
    }
    else if(op=="<="){
        return stoi(lhs)<=stoi(rhs);
    }
    else if(op==">"){
        return stoi(lhs)>stoi(rhs);
    }
    else if(op==">="){
        return stoi(lhs)>=stoi(rhs);
    }
    else{
        cout << "error" ;
        exit(0);
    }
}

int main(){
    vector<vector<string>> table1, table2;
    
    unordered_map<string, int> attribute_idx1, attribute_idx2; 
    
    process_file("Book1.csv", table1, attribute_idx1);
    // process_file("table2.txt", table2, attribute_idx2);
    
    // for(auto &x: attribute_idx1){
    //     cout << x.first << " " << x.second << endl;
    // }
    
    // for(auto &x: table1){
    //     for(auto &y: x){
    //         cout << y << " ";
    //     }
    //     cout << endl;
    // }
    
    // $[(Age=21 && Name="Ayush Gangwar") || Roll_No=1](table1)
    
    string command="$[Age=19 || Name=\"Ayush Gangwar\" || Roll_No=3](table1)";
    // getline(cin, command);
    
    // cout << command << endl;
    
    set<vector<string>> result;
    if(command[0]=='$'){
        string exp;
        for(int i=0, f=0; i<command.size(); i++){
            if(f==1){
                if(command[i]==']') break;
                exp.push_back(command[i]);
            }
            if(command[i]=='['){
                f=1;
            }
        }
        
        // cout << exp << endl;
        
        // checking for kth row of table1
        for(int k=0; k<table1.size(); k++){
            string bool_exp;
            for(int i=0; i<exp.size(); i++){
                if(exp[i]=='=' || exp[i]=='<' || exp[i]=='>' || exp[i]=='!'){
                    string lhs;
                    int j;
                    for(j=i-1; j>=0; j--){
                        if(exp[j]==' ' || exp[j]=='(' || exp[j]=='&' || exp[j]=='|' || exp[j]=='!'){
                            break;
                        }
                        lhs.push_back(exp[j]);
                    }
                    
                    reverse(lhs.begin(), lhs.end());
                    
                    string op;
                    op.push_back(exp[i]);
                    j=i+1;
                    if(exp[j]=='='){
                        op.push_back(exp[j]);
                        j++;
                    }
                    
                    string rhs;
                    bool quotes=0;
                    for(; j<exp.size(); j++){
                        if(quotes==0 && (exp[j]==' ' || exp[j]==')' || exp[j]=='&' || exp[j]=='|' || exp[j]=='!')){
                            break;
                        }
                        
                        if(exp[j]=='"'){
                            quotes^=1;
                        }
                        else rhs.push_back(exp[j]);
                    }
                    
                    // cout << attribute_idx1[lhs]<< " " << lhs << " " << op << " " << rhs << endl;
                    bool_exp.push_back('0'+check_condition(table1[k][attribute_idx1[lhs]], op, rhs));
                }
                else if(exp[i]=='(' || exp[i]==')'){
                    bool_exp.push_back(exp[i]);
                }
                else if(exp[i]=='&' || exp[i]=='|' || exp[i]=='!'){
                    if(bool_exp.back()!=exp[i]){
                        bool_exp.push_back(exp[i]);
                    }
                }
            }
            
            // cout << bool_exp << endl;
            string postfix=infix_to_postfix(bool_exp);
            // cout << postfix << endl;
            bool res=evaluate(postfix);
            // cout << res << endl;
            
            if(res){
                result.insert(table1[k]);
            }
        }
    }
    else{
        //
    }
    
    for(auto &x: result){
        for(auto &y: x){
            cout << y << " ";
        }
        cout << endl ;
    }
    
    return 0;
}

// + ^ - *[](theta join) @(cross product) $[](sigma) #[](project) %[](rename, rho) /(division)

// complete set of operators :- sigma, project, cross pr, union, difference

// a+b
// $[]() + $[]()

// 
// #[deptId](dept) - #[deptId]($[Sex="F"](professor))
#include <bits/stdc++.h>
#include "table_data_structure.h"
#include "open_file.h"
#include "all_operators.h"
#include "infix_to_postfix.h"

using namespace std;


Table* evaluate(string command){
    vector<string> postfix = infix_to_postfix(command);
    
    // for(auto &x: postfix){
    //     cout << x << " " ;
    // }
    
    // exit(0);
    
    stack<Table *> st;
    
    for(int i=0; i<postfix.size(); i++){
        if(isOperand(postfix[i][0])){
            st.push(open_file(postfix[i]));
        }
        else{
            // for unary operator
            if(postfix[i][0]=='$' || postfix[i][0]=='#' || postfix[i][0]=='%'){
                Table *a=st.top(); st.pop();
                st.push(do_operation(a, postfix[i], NULL));
                
                delete(a);
            }
            // for binary operator
            else{
                Table *b=st.top(); st.pop(); 
                Table *a=st.top(); st.pop();
                
                st.push(do_operation(a, postfix[i], b));
                
                delete(a); delete(b);
            }
        }
    }
    return st.top();
}

int main(){
    // symbols used for different RA operators
    // sigma : $[condition use && for AND, || for OR, ! for NOT]
    // project : #[attributes comma separated]
    // rename(rho) : %(not implemented yet)
    // union : +
    // intersection : ^
    // set difference : -
    // theta join : *[condition]
    // cross product : @
    // division : /
    
    // Sample tables are given as Book1, Book2 etc.
    
    // SAMPLE COMMANDS
    string command;
    command = "$[Age=21](#[Name, Age]($[Roll_No=1](Book1)))";
    // command="#[Age, Roll_No, Name]($[(Age=19 && Name=\"Ayush Gangwar\") || Roll_No=3](Book1))";
    // command = "Book1 + Book3";
    // command = "Book1 ^ Book3";
    // command = "Book1 - Book3";
    // command = "Book1 *[Roll_No = Student_Id] Book6";
    // command = "Book1 @ Book2";
    // command = "Book4 / Book5";
    
    cout << "Command is: " << command << endl;
    cout << endl;
    
    cout << "Result is: " << endl;
    Table *result = evaluate(command);
    
    // for(auto &x: (result->attributes)){
    //     cout << x << "\t\t\t";
    // }
    // cout << endl;
    
    for(auto &x: (result->data)){
        for(auto &y: x){
            cout << y << "\t";
        }
        cout << endl;
    }
    
    return 0;
}
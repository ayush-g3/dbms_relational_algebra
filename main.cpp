#include <bits/stdc++.h>
#include "table_data_structure.h"
#include "file_handling.h"
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

void print_table(Table* result){
    vector <int> space((result->attributes).size(), 0);
    int p=0;
    for(int j=0; j<(result->attributes).size(); j++){
        space[j] = (result->attributes)[j].size();
        
    	for(int k=0; k<(result->data).size(); k++){
    		if((result->data)[k][j].size()>space[j])
    	        space[j]=(result->data)[k][j].size();
    	}
        
    	p+=space[j];
    }
    cout<<"\n  ";
    for(int j=0; j<(result->attributes).size(); j++){
        cout << left << setw(space[j]+1) << setfill(' ') << (result->attributes)[j]<<"  |  ";
    }
    cout<<"\n";
    for(int j=0; j<7*(result->attributes).size()+p; j++) cout<<"-";
    cout<<"\n  ";
    for(int j=0; j<(result->data).size(); j++){
        for(int k=0; k<(result->data)[j].size(); k++)
            cout << left << setw(space[k]+1) << setfill(' ') <<(result->data)[j][k]<<"  |  ";
        cout<<"\n  ";
    }
    cout<<"\n";
}

int main(){
    // symbols used for different RA operators
    // sigma : $[condition use && for AND, || for OR, ! for NOT]
    // project : #[attributes comma separated]
    // rename : %[new attribute names comma separated]
    // union : +
    // intersection : ^
    // set difference : -
    // theta join : *[condition]
    // cross product : @
    // division : /
    // for saving the result use <-
    // give the string/character literals within double quotes
    
    // Sample tables are given as Book1, Book2 etc.
    
    // SAMPLE COMMANDS
    string command;
    // command = "temp <- $[Age=21](#[Name, Age]($[Roll_No=1](Book1)))";
    // command = "$[Age=21](#[Name, Age]($[Roll_No=1](Book1)))";
    // command="#[Age, Roll_No, Name]($[(Age=19 && Name=\"Ayush Gangwar\") || Roll_No=3](Book1))";
    // command = "%[roll2, name2, age2](Book1)";
    // command = "Book1 + Book3";
    // command = "Book1 ^ Book3";
    // command = "Book1 - Book3";
    // command = "Book1 *[Roll_No = Student_Id] Book6";
    // command = "Book1 @ Book2";
    // command = "Book4 / Book5";
    
    while(1){
        cout << "Enter Command: ";
        getline(cin, command);
        
        if(command == "exit"){
            break;
        }
        
        bool save=0; string save_name;
        size_t found = command.find("<-");
        if(found != string::npos){
            save=1;
            save_name=command.substr(0, found);
            command=command.substr(found+2);
        }
        
        try{
            Table *result = evaluate(command);
            if(result!=NULL){
                print_table(result);
                
                if(save){
                    write_file(result, save_name);
                    cout << "Result has been saved!\n" << endl;
                }
            }
            else{
                cout << "NULL returned" << endl;
            }
            
        }
        catch (...){
            cout << "An Error Occured" << endl;
        }
    }
    
    return 0;
}
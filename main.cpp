#include <bits/stdc++.h>
#include "table_data_structure.h"
#include "file_handling.h"
#include "all_operators.h"
#include "infix_to_postfix.h"

using namespace std;

// function to evaluate the command
Table* evaluate(string command){
    vector<string> postfix = infix_to_postfix(command);
    
    stack<Table *> st;
    
    for(int i=0; i<postfix.size(); i++){
        if(isOperand(postfix[i][0])){
            Table* table=open_file(postfix[i]);
            if(table==NULL) return NULL;
            st.push(table);
        }
        else{
            // for unary operator
            if(postfix[i][0]=='$' || postfix[i][0]=='#' || postfix[i][0]=='%'){
                Table *a=st.top(); st.pop();
                Table* table=do_operation(a, postfix[i], NULL);
                if(table==NULL) return NULL;
                st.push(table);
                
                delete(a);
            }
            // for binary operator
            else{
                Table *b=st.top(); st.pop(); 
                Table *a=st.top(); st.pop();
                
                Table* table=do_operation(a, postfix[i], b);
                if(table==NULL) return NULL;
                st.push(table);
                
                delete(a); delete(b);
            }
        }
    }
    
    if(st.size()>0) return st.top();
    return NULL;
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
    string command;
    
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
            cout << "Some Error Occured" << endl;
        }
    }
    
    return 0;
}
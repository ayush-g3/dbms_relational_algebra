#ifndef ALL_OPERATORS_H
#define ALL_OPERATORS_H

#include<bits/stdc++.h>
#include "table_data_structure.h"
#include "condition_checking.h"
#include "open_file.h"

using namespace std;

Table* operator_sigma(Table* table, string oper){
    
    // extracting the condition given in []
    string cond;
    for(int i=0, f=0; i<oper.size(); i++){
        if(f==1){
            if(oper[i]==']') break;
            cond.push_back(oper[i]);
        }
        if(oper[i]=='['){
            f=1;
        }
    }
    
    // cout << "cond: " << cond << endl;
    
    set<vector<string>> result;
    // checking for kth row of table a
    for(int k=0; k<(table->data).size(); k++){
        if(does_satisfy_cond(cond, table, k)){
            result.insert((table->data)[k]);
        }
    }
    
    // create a new result table pointer and store result in it
    Table *result_table = new Table();
    
    // (result_table->attribute_idx)=(table->attribute_idx);
    (result_table->attributes)=(table->attributes);
    
    for(auto &row: result){
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* operator_project(Table *table, string oper){
    // #[Roll_No]
    string attributes;
    for(int i=0, f=0; i<oper.size(); i++){
        if(f==1){
            if(oper[i]==']') break;
            attributes.push_back(oper[i]);
        }
        if(oper[i]=='['){
            f=1;
        }
    }
    
    vector<string> attribute_list = row_to_vector(attributes);
    
    // for(auto &x: attribute_list){
    //     cout << x << " ";
    // }
    // exit(0);
    
    vector<int> idx;
    // for(auto &x: attribute_list){
    //     idx.push_back((table->attribute_idx)[x]);
    // }
    for(auto &x: attribute_list){
        for(int i=0; i<(table->attributes).size(); i++){
            if(x==(table->attributes)[i]){
                idx.push_back(i);
                break;
            }
        }
    }
    
    vector<string> required_attributes;
    for(auto &x: idx){
        required_attributes.push_back((table->attributes)[x]);
    }
    
    Table *result_table = new Table();
    
    (result_table->attributes) = required_attributes;
    // for(int i=0; i<required_attributes.size(); i++){
    //     (table->attribute_idx)[required_attributes[i]]=i;
    // }
    for(int i=0; i<(table->data).size(); i++){
        vector<string> row;
        for(auto &x: idx){
            row.push_back((table->data)[i][x]);
        }
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* do_operation(Table *a, string oper, Table *b){
    if(oper[0]=='$'){
        return operator_sigma(a, oper);
    }
    else if(oper[0]=='#'){
        return operator_project(a, oper);
    }
    else{
        //
    }
}

#endif
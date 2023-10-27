#ifndef ALL_OPERATORS_H
#define ALL_OPERATORS_H

#include<bits/stdc++.h>
#include "table_data_structure.h"
#include "condition_checking.h"
#include "file_handling.h"

using namespace std;

string extract_from_square_brackets(string oper){
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
    
    return cond;
}

Table* operator_sigma(Table* table, string &cond){
    
    // cout << "cond: " << cond << endl;
    
    set<vector<string>> result_set;
    // checking for kth row of table a
    for(int k=0; k<(table->data).size(); k++){
        if(does_satisfy_cond(cond, table, k)){
            result_set.insert((table->data)[k]);
        }
    }
    
    // create a new result table pointer and store result in it
    Table *result_table = new Table();
    
    // (result_table->attribute_idx)=(table->attribute_idx);
    (result_table->attributes)=(table->attributes);
    
    for(auto &row: result_set){
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* operator_project(Table *table, vector<string> &attribute_list){
    // #[Roll_No]
    
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
    set<vector<string>> result_set;
    for(int i=0; i<(table->data).size(); i++){
        vector<string> row;
        for(auto &x: idx){
            row.push_back((table->data)[i][x]);
        }
        result_set.insert(row);
    }
    
    for(auto &row: result_set){
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* operator_rename(Table *table, vector<string> &new_attribute_list){
    // %[Roll_No, Name](Book1)
    if(new_attribute_list.size()!=(table->attributes).size()){
        cout << "No of attributes in rename operator is not valid!" << endl;
        exit(0);
    }
    
    Table *result_table = new Table();
    (result_table->attributes)=new_attribute_list;
    for(auto &x: table->data){
        (result_table->data).push_back(x);
    }
    
    return result_table;
}

Table *operator_cross_product(Table *table1, Table *table2){
    // the two tables should not have any common attribute names
    Table *result_table = new Table();
    
    for(auto &x: (table1->attributes)){
        (result_table->attributes).push_back(x);
    }
    for(auto &x: (table2->attributes)){
        (result_table->attributes).push_back(x);
    }
    
    int size1=(table1->data).size();
    int size2=(table2->data).size();
    
    set<vector<string>> result_set;
    for(int i=0; i<size1; i++){
        for(int j=0; j<size2; j++){
            vector<string> row; 
            row.insert( 
                row.end(), ((table1->data)[i]).begin(), (table1->data)[i].end()
            );
            row.insert( 
                row.end(), ((table2->data)[j]).begin(), (table2->data)[j].end()
            );
            
            result_set.insert(row);
        }
    }
    
    for(auto &row: result_set){
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* operator_union(Table *table1, Table *table2){
    // check union compatiblity
    if((table1->data)[0].size() != (table2->data)[0].size()){
        cout << "Union Incompatible" << endl;
        exit(0);
    }
    
    set<vector<string>> result_set;
    for(auto &x: (table1->data)){
        result_set.insert(x);
    }
    for(auto &x: (table2->data)){
        result_set.insert(x);
    }
    
    Table *result_table = new Table();
    (result_table->attributes) = (table1->attributes);
    for(auto &row: result_set){
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* operator_set_difference(Table *table1, Table *table2){
    // check union compatibility
    if((table1->data)[0].size() != (table2->data)[0].size()){
        cout << "Union Incompatible" << endl;
        exit(0);
    }
    
    set<vector<string>> result_set;
    for(auto &x: (table1->data)){
        result_set.insert(x);
    }
    for(auto &x: (table2->data)){
        auto it=result_set.find(x);
        if(it!=result_set.end()){
            result_set.erase(it);
        }
    }
    
    Table *result_table = new Table();
    (result_table->attributes) = (table1->attributes);
    for(auto &row: result_set){
        (result_table->data).push_back(row);
    }
    
    return result_table;
}

Table* operator_intersection(Table *table1, Table *table2){
    Table *t1 = operator_union(table1, table2);
    Table *t2 = operator_union(operator_set_difference(table1, table2), operator_set_difference(table2, table1));
    
    Table *result_table = operator_set_difference(t1, t2);
    
    delete(t1);
    delete(t2);
    
    return result_table;
}

Table* operator_division(Table *table1, Table *table2){
    set<string> attribute_set;
    for(auto &x: (table1->attributes)){
        attribute_set.insert(x);
    }
    for(auto &y: (table2->attributes)){
        auto it=attribute_set.find(y);
        if(it!=attribute_set.end()){
            attribute_set.erase(it);
        }
    }
    
    vector<string> attribute_list(attribute_set.begin(), attribute_set.end());
    
    Table *t1=operator_project(table1, attribute_list);
    Table *t2=operator_project(operator_set_difference(operator_cross_product(t1, table2), table1), attribute_list);
    
    Table *result_table = operator_set_difference(t1, t2);
    
    delete(t1);
    delete(t2);
    
    return result_table;
}

Table* operator_join(Table* table1, string &cond, Table* table2){
    // cout << cond << endl; exit(0);
    return operator_sigma(operator_cross_product(table1, table2), cond);
}

Table* do_operation(Table *a, string oper, Table *b){
    // complete set of operators $ # @ + -
    if(oper[0]=='$'){
        string condition = extract_from_square_brackets(oper);
        return operator_sigma(a, condition);
    }
    else if(oper[0]=='#'){
        string attributes = extract_from_square_brackets(oper);
        vector<string> attribute_list = row_to_vector(attributes);
        return operator_project(a, attribute_list);
    }
    else if(oper[0]=='%'){
        string new_attributes = extract_from_square_brackets(oper);
        vector<string> new_attribute_list = row_to_vector(new_attributes);
        return operator_rename(a, new_attribute_list);
    }
    else if(oper[0]=='@'){
        return operator_cross_product(a, b);
    }
    else if(oper[0]=='+'){
        return operator_union(a, b);
    }
    else if(oper[0]=='-'){
        return operator_set_difference(a, b);
    }
    else if(oper[0]=='^'){
        return operator_intersection(a, b);
    }
    else if(oper[0]=='/'){
        return operator_division(a, b);
    }
    else if(oper[0]=='*'){
        string condition = extract_from_square_brackets(oper);
        return operator_join(a, condition, b);
    }
    else{
        cout << "Invalid Operator!" << endl;
        exit(0);
    }
}

#endif
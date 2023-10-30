#ifndef ALL_OPERATORS_H
#define ALL_OPERATORS_H

#include<bits/stdc++.h>
#include "table_data_structure.h"
#include "condition_checking.h"
#include "file_handling.h"

using namespace std;

// extracts the string within square brackets [abc] -> abc
string extract_from_square_brackets(string oper){
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
    
    return cond;
}

Table* operator_sigma(Table* table, string &cond){
    // $[age=21](Book1)
    // cond : age=21
    
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
    // #[Roll_No, Name](Book1)
    // attribute_list : Roll_No, Name
    
    vector<int> idx;
    for(auto &x: attribute_list){
        for(int i=0; i<(table->attributes).size(); i++){
            if(to_lowercase(x) == to_lowercase((table->attributes)[i])){
                idx.push_back(i);
                break;
            }
        }
    }
    
    vector<string> required_attributes;
    for(auto &x: idx){
        required_attributes.push_back((table->attributes)[x]);
    }
    
    if(required_attributes.size()!=attribute_list.size()){
        cout << "Invalid attribute in project operator!" << endl;
        return NULL;
    }
    
    
    Table *result_table = new Table();
    
    (result_table->attributes) = required_attributes;
    
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
    // %[Roll_No2, Name2](#[Roll_No, Name](book1))
    // new_attribute_list : Roll_No2, Name2
    
    if(new_attribute_list.size()!=(table->attributes).size()){
        cout << "No of attributes in rename operator is not valid!" << endl;
        return NULL;
    }
    
    Table *result_table = new Table();
    (result_table->attributes)=new_attribute_list;
    set<vector<string>> result_set;
    for(auto &x: table->data){
        result_set.insert(x);
    }
    
    for(auto &x: result_set){
        (result_table->data).push_back(x);
    }
    
    return result_table;
}

Table *operator_cross_product(Table *table1, Table *table2){
    // ideally the two tables should not have any common attribute names 
    // because can't do table1.attr and tabl2.attr
    
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
    if((table1->attributes).size() != (table2->attributes).size()){
        cout << "Union Incompatible" << endl;
        return NULL;
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
    if((table1->attributes).size() != (table2->attributes).size()){
        cout << "Union Incompatible" << endl;
        return NULL;
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
    Table *t2=operator_project(operator_set_difference(operator_project(operator_cross_product(t1, table2), table1->attributes), table1), attribute_list);
    
    Table *result_table = operator_set_difference(t1, t2);
    
    delete(t1);
    delete(t2);
    
    return result_table;
}

Table* operator_join(Table* table1, string &cond, Table* table2){
    // ideally the two tables should not have any common attribute names 
    // because can't do table1.attr and tabl2.attr
    return operator_sigma(operator_cross_product(table1, table2), cond);
}

Table* operator_left_join(Table* table1, string &cond, Table* table2){
    Table* tmp = operator_join(table1, cond, table2);
    
    Table* null_table = new Table();
    null_table->attributes = table2->attributes;
    vector<string> null_vector((table2->attributes).size(), "NULL");
    (null_table->data).push_back(null_vector);
    
    Table* result_table = operator_union(tmp, operator_cross_product(operator_set_difference(table1, operator_project(tmp, table1->attributes)), null_table));
    
    delete(null_table);
    return result_table;
}

Table* operator_right_join(Table* table1, string &cond, Table* table2){
    Table* tmp = operator_join(table1, cond, table2);
    
    Table* null_table = new Table();
    null_table->attributes = table1->attributes;
    vector<string> null_vector((table1->attributes).size(), "NULL");
    (null_table->data).push_back(null_vector);
    
    Table *result_table = operator_union(tmp, operator_cross_product(null_table, operator_set_difference(table2, operator_project(tmp, table2->attributes))));
    
    delete(null_table);
    return result_table;
}

Table* do_operation(Table *a, string oper, Table *b){
    // complete set of operators $ # @ + -
    if(oper[0]=='$'){
        string condition = extract_from_square_brackets(oper);
        return operator_sigma(a, condition);
    }
    else if(oper[0]=='#'){
        string attributes = extract_from_square_brackets(oper);
        vector<string> attribute_list = split_by_comma(attributes);
        return operator_project(a, attribute_list);
    }
    else if(oper[0]=='%'){
        string new_attributes = extract_from_square_brackets(oper);
        vector<string> new_attribute_list = split_by_comma(new_attributes);
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
    else if(oper[0]=='*' && oper[1]=='~'){
        string condition = extract_from_square_brackets(oper);
        return operator_right_join(a, condition, b);
    }
    else if(oper[0]=='*'){
        string condition = extract_from_square_brackets(oper);
        return operator_join(a, condition, b);
    }
    else if(oper[0]=='~' && oper[1]=='*'){
        string condition = extract_from_square_brackets(oper);
        return operator_left_join(a, condition, b);
    }
    else{
        cout << "Invalid Operator!" << endl;
        return NULL;
    }
}

#endif
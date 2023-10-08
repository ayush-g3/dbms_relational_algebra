#ifndef OPEN_FILE_H
#define OPEN_FILE_H

#include <bits/stdc++.h>
#include "table_data_structure.h"

using namespace std;

string remove_front_back_spaces(string s){
    int f=0;
    while(f<s.size() && s[f]==' ') f++;
    int b=s.size()-1;
    while(b>=0 && s[b]==' ') b--;
    
    string res;
    for(int i=f; i<=b; i++){
        res.push_back(s[i]);
    }
    
    return res;
}

vector<string> row_to_vector(string &row){
    string tmp;
    vector<string> extracted_row;
    for(auto &x: row){
        if(x==','){
            extracted_row.push_back(remove_front_back_spaces(tmp));
            tmp.clear();
            continue;
        }
        tmp.push_back(x);
    }
    extracted_row.push_back(remove_front_back_spaces(tmp));
    return extracted_row;
}

Table* open_file(string file_name){
    Table* table=new Table();
    
    ifstream file;
    string line;
    
    file.open(file_name+".csv");
    
    // processing the row of the attributes
    getline(file, line);
    vector<string> attributes = row_to_vector(line);
    (table->attributes) = attributes;
    // for(int i=0; i<attributes.size(); i++){
    //     (table->attribute_idx)[attributes[i]]=i;
    // }
    
    // processing other rows
    while(getline(file, line)){
        (table->data).push_back(row_to_vector(line));
    }
    
    file.close();
    
    return table;
}

#endif
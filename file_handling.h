#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

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
    
    file.open("database/"+file_name+".csv");
    
    if(!file.good()){
        cout << "File not found!" << endl;
        exit(0);
    }
    
    // processing the row of the attributes
    getline(file, line);
    vector<string> attributes = row_to_vector(line);
    (table->attributes) = attributes;
    
    // processing other rows
    while(getline(file, line)){
        (table->data).push_back(row_to_vector(line));
    }
    
    file.close();
    
    return table;
}

void write_file(Table* table, string name){
    ofstream file;
    
    name=remove_front_back_spaces(name);
    file.open("database/"+name+".csv");
    
    int n=(table->attributes).size();
    for(int i=0; i<n; i++){
        file << (table->attributes)[i];
        if(i<n-1){
            file << ",";
        }
    }
    file << "\n";
    
    for(auto &row: table->data){
        for(int i=0; i<n; i++){
            file << row[i];
            if(i<n-1){
                file << ",";
            }
        }
        file << "\n";
    }
    file.close();
}

#endif
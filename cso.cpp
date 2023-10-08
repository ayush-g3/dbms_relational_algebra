#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main(){
    vector<vector<string>> A, B, AB;
    A={{"1", "Ayush Gangwar", "21"},{"2", "Aditya Vats", "19"}};
    B={{"DBMS", "A"},{"CG", "A-"}};
    
    int size1=(A).size();
    int size2=(B).size();
    
    for(int i=0; i<size1; i++){
        for(int j=0; j<size2; j++){
            vector<string> row;
            // AB.reserve( A.size() + B.size() ); // preallocate memory
            row.insert( row.end(), A[i].begin(), A[i].end() );
            row.insert( row.end(), B[j].begin(), B[j].end() );
            
            AB.push_back(row);
        }
    }
    cout << AB.size() << endl;
    for(auto &x: AB){
        for(auto &y: x){
            cout << y << " ";
        }
        cout << endl;
    }
    
    return 0;
}
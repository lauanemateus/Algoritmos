#include<bits/stdc++.h>
using namespace std;

//BitMask
// imprimir todos subconjuntos de um conjunto com n elementos

int main(){
    int n;
    cin>>n;
    cout << "{ ";
    for(int i = 1; i <= (1 << n); i++){
        cout << "(" ;
        for(int j=0; j<n; j++){
            if(i & (1 << j)){
                cout << j+1;
            }
        }
        if(i != 1 << n)
            cout << "),";
        else cout << ") }\n" ; 
    }
    return 0;
}
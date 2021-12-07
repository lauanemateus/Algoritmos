#include<iostream>
using namespace std;

bool eh_primo(int x){
    if(x==1) return 0;
    for(int i=2;i*i <= x; i++){
        if(x%i==0) return 0;
    }
    return 1;
}
int main(){
    int n;
    while( scanf("%d", &n) != EOF ){
        if(!eh_primo(n)) printf("%d nao eh primo\n", n);
        else printf("%d eh primo\n", n);
    }
    return 0;
}
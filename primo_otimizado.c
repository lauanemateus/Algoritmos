#include<stdio.h>
#include<math.h>


bool eh_primo(int x){
    if(x==1) return 0;
    for(int i=2;i*i <= x; i++){
        if(x%i==0) return 0;
    }
    return 1;
}
int main(){
    int n;
    scanf("%d", &n);
        if(!eh_primo(n)) printf("N\n");
        else printf("S\n");
    return 0;
}
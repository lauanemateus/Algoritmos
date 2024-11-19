#include<stdio.h>

#define MAXN 10000
#define MAXM 1001

void SelectionSort(int v[], int V[], int n){
    int i,j;
    int menor = MAXM , ind;
    for(i=0;i<n;i++){
        menor = MAXM;
        for(j=i;j<n;j++){
            if(v[j]<menor){
                menor = v[j];
                ind = j;
            }
        }
        v[ind] = v[i];
        v[i] = menor;

    }
}

int main(){
    int v[MAXN], V[MAXM],i,j, n;
    while(scanf("%d", &n), n){
        for(i=0;i<n;i++){
            scanf("%d", &v[i]);
        }
        SelectionSort(v, V, n);
        for(i=0;i<n;i++){
            if(i!=n-1) printf("%d ", v[i]);
            else printf("%d\n", v[i]);
        }
    }
    //printf("\n");
    return 0;
}

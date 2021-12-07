#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2001;
int size[MAXN], value[MAXN], S, N, dp[MAXN][MAXN];

int knapsack(int i, int tamanho){
    if(i == N || tamanho == 0) return dp[i][tamanho] = 0; // a função continua para  0 <= i <= N-1
    if(dp[i][tamanho]!=0) return dp[i][tamanho];

    int ans = knapsack(i+1, tamanho);
    if(size[i]<=tamanho){
        int coloca = value[i] + knapsack(i+1, tamanho-size[i]);
        ans = max(ans,coloca);
    }
    return dp[i][tamanho] = ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>S>>N;
    for(int i=0;i<N;i++){
        cin>>size[i]>>value[i];
    }
    cout << knapsack(0,S) << "\n"; // dp[0][S] representa a mochila com maior quantidade de elemntos
    // dp[N][S] é a mochila com zero elementos
    // dp[N-1][S] é a mochila até 1 elemntos, e assim por diante
    return 0;
}
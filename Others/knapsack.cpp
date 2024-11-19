#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2001;
int size[MAXN], value[MAXN], S, N, dp[MAXN][MAXN];

int knapsack(int i, int tamanho){
    if(i == 0 || tamanho == 0) return dp[i][tamanho] = 0;
    if(dp[i][tamanho]!=0) return dp[i][tamanho];

    int ans = knapsack(i-1, tamanho);
    if(size[i]<=tamanho){
        int coloca = value[i] + knapsack(i-1, tamanho-size[i]);
        ans = max(ans,coloca);
    }
    return dp[i][tamanho] = ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>S>>N;
    for(int i=1;i<=N;i++){
        cin>>size[i]>>value[i];
    }
    cout << knapsack(N,S) << "\n";
    return 0;
}

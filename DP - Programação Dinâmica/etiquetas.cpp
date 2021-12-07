// OBI 2019 Nível Sênior 3° fase 
// https://olimpiada.ic.unicamp.br/pratique/pu/2019/f3/etiquetas/

#include<bits/stdc++.h>
using namespace std;

const int MAXN = (int)1e4 + 5;
const int INF = 1000000000;

int N,K,C;
int dp[MAXN][MAXN]; // a dp descreve a melhor solução para cada k com os valores dos indices 1 a i 
int v[MAXN];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>N>>K>>C;

    /*for(int i=0;i<=K;i++){
        for(int j=0;j<=N;j++)
            dp[i][j] = -INF;
    } */
    
    dp[0][0] = 0;
    for(int i=1; i<=N; i++){
        cin>>v[i];
        dp[0][i] = dp[0][i-1] + v[i];
    }

    for(int j=1; j<=K; j++){
        for(int i = j*C; i<=N; i++){

            int nao_coloca = dp[j-1][i-C] ;
            int coloca = dp[j][i-1] + v[i];
            
            if(i == j*C) dp[j][i] = nao_coloca;
            else dp[j][i] = max(nao_coloca, coloca);
        }
    }    
    cout << dp[K][N] << "\n";
    return 0;
}
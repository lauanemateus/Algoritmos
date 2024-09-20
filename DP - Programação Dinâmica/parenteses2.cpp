#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100+10;
const ll inf = 1e15;

int dp[N][N], n;

/*
dp[i][saldo] guarda a resposta de solve(i, saldo)
A dp[i][saldo] representa o seguinte: considerando que eu tenho uma string de 0 ate i-1,
que eu nao sei qual eh, mas eu sei que ela tem um saldo tal;
Saldo eh a diferença dos parenteses que abre com o que fecha;
Quantas strings eu consigo formar de i ate n-1, tal que a string total seja valida? Observe que 
eu nao quero saber quantas strings totais existem, mas eu quero saber quantas strings de i ate n-1 eu
consigo formar com esse saldo.
*/

int solve(int i, int saldo){
    if(i==n){
        if(saldo == 0){
            return 1;
        }
        return 0;
    }
    int &ans = dp[i][saldo];
    if(ans!=-1) return ans;
    
    ans = solve(i+1, saldo+1);
    if(saldo>0) ans += solve(i+1, saldo-1);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;
    memset(dp, -1, sizeof(dp));
    cout<<solve(0,0)<<"\n";
    return 0;
}
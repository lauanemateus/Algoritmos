#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100+10;
const ll inf = 1e15;

int dp[N][N], n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n;

    /* 
    A dp[i][saldo] representa o seguinte: considerando que eu tenho uma string de i+1 ate n,
     que eu nao sei qual eh, mas eu sei que ela tem um saldo tal;
    Saldo eh a diferença dos parenteses que fecha com o que abre;
    Quantas strings eu consigo formar de 1 ate i, tal que a string total seja valida? Observe que 
     eu nao quero saber quantas strings totais existem, mas eu quero saber quantas strings de 1 ate i eu
     consigo formar com esse saldo. Eh a mesma logica da dp recursiva.
    Assim, no momento em que estamos calculando dp[i][saldo] no for, 
     vemos todas as possibilidades para o que colocar na posicao i.
    */

   // agora o saldo eh em relacao ao que fecha

    dp[0][0] = 1; // representa a string vazia

    for(int i=1; i<=n; i++){
        for(int saldo=i; saldo>=0; saldo--){
            if(saldo)
                dp[i][saldo] = dp[i-1][saldo-1] + dp[i-1][saldo+1]; // abrindo e fechando
            else dp[i][saldo] = dp[i-1][saldo+1]; // apenas fechando
        }
    }
    cout<<dp[n][0]<<"\n"; // quantas strings eu consigo formar de 1 a n tal que meu saldo eh 0 (string valida) ?
    return 0;
}
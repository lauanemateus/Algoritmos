#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100+10;
const ll inf = 1e15;
const int mod = 998244353;

int dp[N][N], n;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin>>n>>s;

    int ans=0;
    for (int k = 0; k <= n-s.size(); k++)
    {
        memset(dp, 0, sizeof(dp));
        dp[n][0] = 1; // representa a string vazia
        // vou obrigar a string ser colocada a partir de k     
        for(int i=n-1; i>=0; i--){
            for(int saldo=i; saldo>=0; saldo--){
                if(i>=k && i-k+1<=s.size()){
                    if(saldo>0 && s[i-k]==')'){
                        dp[i][saldo] = dp[i+1][saldo-1];
                    }
                    else if(s[i-k]=='('){
                        dp[i][saldo] = dp[i+1][saldo+1];
                    }
                }
                else{
                    if(saldo)
                        dp[i][saldo] = dp[i+1][saldo-1] + dp[i+1][saldo+1]; // fechando e abrindo
                    else dp[i][saldo] = dp[i+1][saldo+1]; // apenas abrindo
                }
            }
        }
        ans = (ans+dp[0][0])%mod;
    }
    cout<<ans<<"\n";
    return 0;
}
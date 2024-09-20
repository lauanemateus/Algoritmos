#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 100+10;
const ll inf = 1e15;

int dp[N][N], n;
string s;

int solve(int i, int k, int saldo){
    if(i==n){
        if(saldo == 0){
            return 1;
        }
        return 0;
    }
    int &ans = dp[i][saldo];
    if(ans!=-1) return ans;
    
    ans = 0;
    if(i>=k && i-k+1<=s.size()){
        if(s[i-k] == ')'){
            if(saldo)
                ans = solve(i+1, k, saldo-1);
        }
        else{
            ans = solve(i+1, k, saldo+1);
        }
    }
    else{
        ans = solve(i+1, k, saldo+1);
        if(saldo>0) ans += solve(i+1, k, saldo-1);
    }
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin>>n>>s;
    int ans = 0;
    for (int i = 0; i <= n-s.size(); i++)
    {
        memset(dp, -1, sizeof(dp));
        ans += solve(0, i, 0);
    }
    cout<<ans<<"\n";
    // cout<<solve(0,0)<<"\n";
    return 0;
}
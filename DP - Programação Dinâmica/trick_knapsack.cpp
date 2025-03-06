// Given the knapsack problem, if I have N objects and I know that the sum of the objects weight is M
// it is possible do the problem in O(N*sqrt(M)) time instead of O(N*M)
// The ideia is transform the repeated values to unique values (then we have sqrt(M) objects at maximum since 1+2+...+X=M)
// But we have to garantee that with these new values I am able to do all sums I could do before
// So, if I have 5+5+5+5+5+5+5, note that I can just use 5+10+20 (do v[i] = v[i-1]*2)
// This trick is similar to the ideia of this problem from CSES: https://cses.fi/problemset/task/2183/
// In this code, we are solving https://cses.fi/problemset/task/1706

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define ft first
#define sd second
typedef long long ll;
const int N = 1e5+5;
const int K = 25;
const int INF = N;
const ll inf = 1e15;

int n, m, vis[N], qt[N], dp[(int)8e2][N]; // dp -> id, qt atual de pessoas. Eu vou ter o dobro de caras de sqrt(1e5), pois nem sempre terei a quantidade exata de 2^qt-1 caras repetidos
vector<int>adj[N], v;
map<int, int> aux;

int dfs(int x, int bef){
    int ct=1;
    vis[x]=1;
    for(auto u:adj[x]){
        if(u!=bef)
            ct+=dfs(u, x);
    }
    return ct;
}

int solve(int i, int sum){ // quero saber se consigo fazer determinada soma
    if(i==v.size()) return sum==0;
    int &ans = dp[i][sum];
    if(ans!=-1) return ans;
    ans = solve(i+1, sum);
    if(sum-v[i]>=0) ans|=solve(i+1, sum-v[i]);
    return ans;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int a, b;
    cin>>n>>m;
    for (int i = 0; i < m; i++)
    {
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    int comp=0;
    for(int i=1; i<=n; i++){
        if(vis[i]==0){
            comp = dfs(i, i);
            qt[comp]++;
        } 
    }
    
    ll x, sum=0;
    for(int i=1; i<=n; i++){
        x = i;
        sum=0;
        aux.clear();
        while(sum+x<=qt[i]*i){
            sum += x;
            aux[x]++;
            x*=2;
        }
       
        for(int j=0; j<31; j++){
            if((1<<j)&(qt[i]-sum/i)) aux[(1<<j)*i]++;
        }
        qt[i]=0;
        for(auto x:aux) qt[x.ft]+=x.sd;
    }
    memset(dp, -1, sizeof(dp));
    for (int i = 1; i <= n; i++)
    {
        while(qt[i]) v.pb(i), qt[i]--;
    }
    for(int i=1; i<=n; i++){
        if(solve(0, i)) cout<<"1";
        else cout<<"0";
    }
    cout<<"\n";
    return 0;
}

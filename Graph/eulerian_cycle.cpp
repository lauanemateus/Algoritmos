// problema: https://cses.fi/problemset/task/1691

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
 
template<class T> using ordset = tree<
T,
null_type,
less<T>,
rb_tree_tag,
tree_order_statistics_node_update>;
 
#define pb push_back
#define ft first 
#define sd second
typedef long long ll;
typedef pair<int,int> pii;
const int N = 2e5+5;
const ll INF = 1e15;
 
int n, m;
set<int>adj[N];
vector<int> ans;
 
void dfs(int x){
    while(adj[x].empty()==0){
        int u = *adj[x].begin();
        adj[x].erase(u);
        adj[u].erase(x);
        dfs(u); 
    }
    ans.pb(x);
}
 
int solve(){
    cin>>n>>m;
    int a, b, start=1;
    for (int i = 0; i < m; i++)
    {   
        cin>>a>>b;
        adj[a].insert(b);
        adj[b].insert(a);
    }
    // vamos olhar os graus dos caras
    for(int i=1; i<=n; i++){
        if(adj[i].size()%2) return 0; // isso garante que nao ha ponte, ou seja, toda aresta faz parte de um ciclo
    }
    dfs(start); // constroi o caminho euleriano a partir de start
    for (int i = 1; i <=n; i++)
    {
        if(adj[i].size()>0) return 0; // caso o grafo seja desconexo
    }
    reverse(ans.begin(), ans.end());
    return 1;
}
 
int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
 
    if(solve()==0){
        cout<<"IMPOSSIBLE\n";
    }
    else{
        for(auto x:ans){
            cout<<x<<" ";
        }
        cout<<"\n";
    }
    return 0;
}

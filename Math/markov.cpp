// Original problem: https://codeforces.com/group/KqUNBZJnMk/contest/580551/problem/I

#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define ft first
#define sd second
const ll N = 1e6+5;
const ll mod = 1e9+7;

ll fat[N], ifat[N];

ll fast_exp(ll b, ll e){
    ll y=1, x=b;
    while(e){
        if(e%2==1){
            y = (y*x)%mod;
        }
        x = (x*x)%mod;
        e /= 2;
    }
    return y;
}

ll soma(ll x, ll y){
    return (x+y)%mod;
}

ll sub(ll x, ll y){
    return (x-y+mod)%mod;
}

ll mul(ll x, ll y){
    return (x*y)%mod;
}

ll comb(ll n, ll k){
    return fat[n]*ifat[n-k]%mod*ifat[k]%mod;
}

ll modinv(ll x){
	return fast_exp(x , mod - 2);
}

ll solveLinear(vector<vector<ll>>& A, vector<ll>& b, vector<ll>& x) {
	for(ll i=0; i<A.size(); i++){
		for(ll j=0; j<A[i].size(); j++){
			A[i][j] = ((A[i][j])%mod + mod)%mod;
		}
	}
	for(ll i=0; i<b.size(); i++){
		b[i] = (b[i]%mod + mod)%mod;
	}
	ll n = A.size(), m = x.size(), rank = 0, br, bc;
	vector<ll> col(m); 
	for(ll i = 0 ; i < col.size() ; i++) col[i] = i;
	for(ll i=0; i<n; i++) {
		ll v, bv = -1;
		for(ll r=i; r<n; r++) for(ll c=i; c<m; c++)
			if ((v = A[r][c])) {
				br = r, bc = c, bv = v;
				goto found;
			}
		for(ll j=i; j<n; j++) if (b[j]) return -1;
		break;
found:
		swap(A[i], A[br]);
		swap(b[i], b[br]);
		swap(col[i], col[bc]);
		for(ll j=0; j<n; j++) swap(A[j][i], A[j][bc]);
		bv = modinv(A[i][i]);
		for(ll j=i+1; j<n; j++) {
			ll fac = (A[j][i] * bv) % mod;
			b[j] = ((b[j] - fac * b[i]) % mod + mod)%mod;
			for(ll k=i+1; k<m; k++) A[j][k] = ((A[j][k] - fac*A[i][k]) % mod + mod)%mod;
		}
		rank++;
	}

	x.assign(m, 0);
	for (ll i = rank; i--;) {
		b[i] = ((b[i] * modinv(A[i][i]) % mod) + mod) % mod;
		x[col[i]] = b[i];
		for(ll j=0; j<i; j++)
			b[j] = ((b[j] - A[j][i] * b[i])%mod + mod)%mod;
	}
	return rank;
}

const ll MAXR = 505;
vector<ll> adj[MAXR];

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
  
    fat[0] = fat[1] = ifat[0] = ifat[1] = 1;
    for(ll i=2; i<N; i++){
        fat[i] = (fat[i-1]*i)%mod;
        ifat[i] = fast_exp(fat[i], mod-2);
    }

    ll R, S;
    ll a, b;
    cin>>R>>a>>b;

    for(ll estado=0; estado<R; estado++){
        for(ll recebe=1; recebe<=R; recebe++){
            S = estado+recebe;
            if(S>=R){
                adj[estado].pb(R);
            }
            else{
                S = S*(b-a)/b;
                if(S<R)
                    adj[estado].pb(S);
                else  
                    adj[estado].pb(R);
            }
        }
    }

    vector < vector<ll> > equacao;
    vector<ll> X(R+1), B(R+1);
    equacao.resize(R+1);
    for(ll estado=0; estado<R; estado++){
        equacao[estado].resize(R+1, 0);
        B[estado] = (sub(0, 1));
        for(auto prox:adj[estado]){
            equacao[estado][prox] = soma(equacao[estado][prox], mul(1, fast_exp(R, mod-2))); // += 1/R
        }
        equacao[estado][estado] = soma(equacao[estado][estado], sub(0, 1)); 
    }

    equacao[R].resize(R+1, 0);
    equacao[R][R]=1;
    B[R] = 0; // E_R = 0

    solveLinear(equacao, B, X);

    cout<<X[0]<<"\n";
    return 0;
}

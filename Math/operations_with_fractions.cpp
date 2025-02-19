#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define ft first
#define sd second
typedef long long ll;

struct Fraction{
    ll x, y; // the fraction is represented by x/y
    Fraction(): x(0), y(1) {} // default constructor
    Fraction(ll x, ll y) : x(x), y(y) {}

    Fraction operator +(const Fraction &f){
        Fraction ans;
        ll gcd;
        if(this->x == 0){
            gcd = abs(__gcd(f.x, f.y));
            ans = f;
            ans.x/=gcd, ans.y/=gcd;
        }
        else if(f.x == 0){
            gcd = abs(__gcd(this->x, this->y));
            ans = *this;
            ans.x/=gcd, ans.y/=gcd;
        }
        else{
            ans.y = this->y*f.y;
            ans.x = ans.y/this->y*this->x + ans.y/f.y*f.x;
            gcd = abs(__gcd(ans.x, ans.y));
            ans.x /= gcd, ans.y /= gcd;
        }
        return ans;
    }
    
    Fraction operator -(const Fraction &f){
        Fraction ans = f;
        ans.x *= -1;
        ans = *this+ans;
        ll gcd = abs(__gcd(ans.x, ans.y));
        ans.x /= gcd, ans.y /= gcd;
        return ans;
    }
    Fraction operator /(const Fraction &f){
        Fraction ans = *this;
        ans.x *= f.y, ans.y *= f.x;
        ll gcd = abs(__gcd(ans.x, ans.y));
        ans.x /= gcd, ans.y /= gcd;
        return ans;
    }
    Fraction operator *(const Fraction &f){
        Fraction ans = *this;
        ans.x *= f.x, ans.y *= f.y;
        ll gcd = abs(__gcd(ans.x, ans.y));
        ans.x /= gcd, ans.y /= gcd;
        return ans;
    }
    bool operator < (const Fraction &f){
        return this->x*f.y>f.x*this->y;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}

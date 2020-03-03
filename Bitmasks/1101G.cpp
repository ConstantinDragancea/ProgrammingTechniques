/*
Solves problem 1101G from Codeforces
https://codeforces.com/contest/1101/problem/G
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rc(s) return cout << s, 0
#define fi first
#define se second
#define L (nod << 1)
#define R (L | 1)
#define smax(X, Y) ((X) > (Y) ? (X) : (Y))
#define smin(X, Y) ((X) < (Y) ? (X) : (Y))

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
const int MAX_BIT = 30;
//CLOCKS_PER_SEC

int n, x, lol, sz, basis[100];

void insertVector(int mask){
    for (int i=0; i<MAX_BIT; i++){
        if (!(mask & (1<< i))) continue;
        if (!basis[i]){
            basis[i] = mask;
            sz++;
            return;
        }
        mask ^= basis[i];
    }
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> x;
        lol ^= x;
        insertVector(lol);
    }
    if (!lol) rc(-1);
    rc(sz);
}
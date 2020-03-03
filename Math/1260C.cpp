/*
Solves problem 1260C from Codeforces
https://codeforces.com/problemset/problem/1260/C
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll t, r, b, k;

ll gcd(ll a, ll b){
    if (!b) return a;
    return gcd(b, a%b);
}

int main(){
    //ifstream cin ("test.in");
    cin >> t;
    while (t--){
        cin >> r >> b >> k;
        if (r > b) swap(r, b);
        ll aux = gcd(r, b);
        cout << (r *(k-1) + aux < b ? "REBEL\n" : "OBEY\n");
    }
    return 0;
}

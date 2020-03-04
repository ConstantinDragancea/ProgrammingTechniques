/*
Solves problem 203881S from Codeforces
https://codeforces.com/group/qcIqFPYhVr/contest/203881/problem/S
*/
#include <bits/stdc++.h>
//#pragma GCC optimize ("O3")
//#pragma GCC target ("sse4")
//#pragma GCC target ("avx,tune=native")
//Use above if bruteforcing with lots of small operations. Or just use it anytime, there's no downside.
//AVX is better slightly
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
typedef pair <ll, ll> pll;
typedef long double ld;

ll inv(ll a, ll b){
    return (a > 1 ? b - inv(b%a, a)*b/a : 1);
}

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

int n, basis [100], t, x, sz;

void insertVector(int mask){
    for (int i=MAX_BIT - 1; i >= 0; i--){
        if (((1 << i) & mask) == 0) continue;
        if (!basis[i]){
            basis[i] = mask;
            sz++;
            return;
        }
        mask ^= basis[i];
    }
}

int get(int k){
    int ans = 0, left = sz;
    for (int i = MAX_BIT - 1; i >= 0; i--){
        if (!basis[i]) continue;
        if (k > (1 << (left - 1)) && (ans & (1 << i)) == 0) ans ^= basis[i];
        else if (k <= (1 << (left - 1)) && (ans & (1 << i)) > 0) ans ^= basis[i];
        if (k > (1 << (left - 1))) k -= (1 << (left - 1));
        left--;
    }
    return ans;
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    //ofstream cout ("test.out");
    cin >> n;
    while (n--){
        cin >> t >> x;
        if (t == 1) insertVector(x);
        else cout << get(x) << '\n';
    }
    return 0;
}

/*
Solves problem 1206D from Codeforces
https://codeforces.com/contest/1206/problem/D
*/
#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#pragma GCC target ("avx,tune=native")
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
#define N 100010

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

int n, d[N], ans = iinf, d2[N], flag = 1, u[N], lol;
ll a[N];
vector <int> v[100];

void dfs(int i, int pr = -1){
    if (d[i] > 40) return;
    //cout << a[i] << ' ' << pr << '\n';
    for (int bit=0; bit<60; bit++){
        if ((1LL<<bit) & a[i]){
            for (auto it: v[bit]){
                if (it == i || it == pr) continue;
                if (u[it] == flag && d[it] < d[i]){
                    //cout << "ans : " << i << ' ' << it << ' ' << d[i] - d[it] + 1 << '\n';
                    ans = smin(ans, d[i] - d[it] + 1);
                    continue;
                }
                else if (u[it] == flag) continue;
                u[it] = flag;
                d[it] = d[i] + 1; dfs(it, i);
            }
        }

    }
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n;
    if (n < 3) rc(-1);
    for (int i=1; i<=n; i++) cin >> a[i], lol += (a[i] != 0);
    if (lol > 180) rc(3);
    for (int bit=0; bit<60; bit++)
        for (int i=1; i<=n; i++)
            if ((1LL<<bit) & a[i]) v[bit].push_back(i);
    for (int i=1; i<=n; i++){
        u[i] = flag; d[i] = 1;
        dfs(i);
        flag++;
    }
    cout << (ans == iinf ? -1 : ans);
    return 0;
}

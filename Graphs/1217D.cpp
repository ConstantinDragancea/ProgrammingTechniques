/*
Solves problem 1217D from Codeforces
https://codeforces.com/contest/1217/problem/D
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
#define N 5010

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

int n, m, col[N];
bool u[N], u2[N], flag;
vector <pii> v[N];

void dfs(int q){
    u[q] = 1;
    for (auto it: v[q]){
        if (!u[it.fi]){
            dfs(it.fi);
            col[it.se] = 1;
        }
        else if (u2[it.fi]) col[it.se] = 1;
        else col[it.se] = 2, flag = 1;
    }
    u2[q] = 1;
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    //ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n >> m;
    for (int i=1, x, y; i<=m; i++){
        cin >> x >> y;
        v[x].push_back({y, i});
    }
    for (int i=1; i<=n; i++)
        if (!u[i]) dfs(i);
    cout << 1 + flag << '\n';
    for (int i=1; i<=m; i++) cout << col[i] << ' ';
    return 0;
}

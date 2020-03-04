/*
Solves problem 1214D from Codeforces
https://codeforces.com/contest/1214/problem/D
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
#define N 1001000

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

int n, m, ans = 2, d[N], d2[N], fv[N], fv2[N];
char c[2*N];
bool u[N];
queue <pii> Q;

bool bfs(){
    for (int i=1; i<=n*m; i++) d[i] = 0;
    d[1] = 1;
    Q.push({1, 1});
    while (!Q.empty()){
        int i = Q.front().fi, j = Q.front().se;
        //cout << i << ' ' << j << ' ' << d[(i-1)*m + j] << '\n';
        Q.pop();
        if (i < n && !d[i*m + j] && c[i*m + j] == '.'){
            d[i*m + j] = d[(i-1)*m + j] + 1; Q.push({i+1, j});
            fv[d[i*m + j]]++;
        }
        if (j < m && !d[(i-1)*m + j + 1] && c[(i-1)*m + j + 1] == '.'){
            d[(i-1)*m +j+1] = d[(i-1)*m + j] + 1; Q.push({i, j+1});
            fv[d[(i-1)*m +j+1]]++;
        }
    }
    return d[n * m];
}

void bfs2(){
    d2[n * m] = 1;
    Q.push({n, m});
    while (!Q.empty()){
        int i = Q.front().fi, j = Q.front().se;
        //cout << i << ' ' << j << ' ' << d2[(i-1)*m + j] << '\n';
        Q.pop();
        if (i > 1 && !d2[(i-2)*m + j] && c[(i-2)*m + j] == '.'){
            d2[(i-2)*m + j] = d2[(i-1)*m + j] + 1;
            Q.push({i-1, j});
            fv2[d2[(i-2)*m +j]]++;
        }
        if (j > 1 && !d2[(i-1)*m + j - 1] && c[(i-1)*m + j - 1] == '.'){
            d2[(i-1)*m + j - 1] = d2[(i-1)*m + j] + 1;
            Q.push({i, j-1});
            fv2[d2[(i-1)*m + j - 1]]++;
        }
    }
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n >> m;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++) cin >> c[(i-1)*m + j];
    for (int i=n; i; i--)
        for (int j=m; j; j--){
            if (i == n && j == m) continue;
            if (j == m && c[i*m + j] == '#') c[(i-1)*m + j] = '#';
            else if (i == n && c[(i-1)*m + j + 1] == '#') c[(i-1)*m + j] = '#';
            else if (i < n && j < m && c[i*m + j] == '#' && c[(i-1)*m + j + 1] == '#') c[(i-1)*m + j] = '#';
        }
    if (!bfs()) rc(0);
    if (n == 1 || m == 1) rc(1);
    bfs2();
    //for (int i=1; i<=n+m; i++) cout << i << " : "  << fv[i] << '\n';
    //for (int i=1; i<=n+m; i++) cout << i << " : "  << fv2[i] << '\n';
    for (int i=2; i<n + m-1; i++)
        if (fv[i] == 1 || fv2[i] == 1) rc(1);
    rc(2);
    return 0;
}

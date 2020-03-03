/*
Solves problem 1245D from Codeforces
https://codeforces.com/contest/1245/problem/D
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define rc(s) return cout << s, 0
#define fi first
#define se second
#define L (nod << 1)
#define R (L  1)
#define smax(X, Y) ((X) > (Y) ? (X) : (Y))
#define smin(X, Y) ((X) < (Y) ? (X) : (Y))
#define N 2100

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

struct edge{
    int a, b;
    ll c;

    bool operator<(const edge &aux)const{
        return c < aux.c;
    }
} M[N*N];
int n, m, comp, p[N], conn;
pii a[N];
ll k[N], ans;
bool u[N];
vector <pii> pairs;

int fnd(int q){
    if (q == p[q]) return q;
    p[q] = fnd(p[q]);
    return p[q];
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n;
    for (int i=1; i<=n; i++) cin >> a[i].fi >> a[i].se;
    for (int i=1, x; i<=n; i++){
        cin >> x;
        M[++m] = {0, i, x};
        p[i] = i;
    }
    for (int i=1; i<=n; i++) cin >> k[i];
    for (int i=1; i<n; i++)
        for (int j=i+1; j<=n; j++)
            M[++m] = {i, j, (k[i] + k[j]) * (abs(a[i].fi - a[j].fi) + abs(a[i].se - a[j].se))};
    sort(M+1, M+1+m);
    for (int i=1; comp < n; i++){
        int st = fnd(M[i].a), dr = fnd(M[i].b);
        if (st == dr) continue;
        p[st] = dr;
        ans += M[i].c;
        comp++;
        if (!M[i].a) u[M[i].b] = 1, conn++;
        else pairs.push_back({M[i].a, M[i].b});
    }
    cout << ans << '\n';
    cout << conn << '\n';
    for (int i=1; i<=n; i++)
        if (u[i]) cout << i << ' ';
    cout << '\n';
    cout << pairs.size() << '\n';
    for (auto it: pairs)
        cout << it.fi << ' ' << it.se << '\n';
    return 0;
}

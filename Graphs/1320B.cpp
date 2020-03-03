/*
Solves problem 1321D / 1320B from Codeforces
https://codeforces.com/problemset/problem/1320/B
The idea is fairly simple, the algorithm used is a basic BFS starting from the end node
going in the opposite way for each edge
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
#define N 200100

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

int n, m, ans1, ans2, d[N], a[N], k;
vector <int> v[N], g[N];
queue <int> Q;

int main(){
    cin >> n >> m;
    for (int i=1, x, y; i<=m; i++){
        cin >> x >> y;
        v[x].push_back(y);
        g[y].push_back(x);
    }
    cin >> k;
    for (int i=1; i<=k; i++) cin >> a[i];
    Q.push(a[k]); d[a[k]] = 1;
    while (!Q.empty()){
        int q = Q.front();
        Q.pop();
        for (auto it: g[q])
            if (!d[it]) d[it] = d[q] + 1, Q.push(it);
    }
    for (int i=2; i<=k; i++){
        if (d[a[i]] != d[a[i-1]] - 1) ans1++, ans2++;
        else{
            int cnt = 0;
            for (auto it: v[a[i-1]])
                if (d[it] == d[a[i-1]] - 1) cnt++;
            if (cnt > 1) ans2++;
        }
    }
    cout << ans1 << ' ' << ans2;
    return 0;
}

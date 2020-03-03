/*
Solves problem 1257D from Codeforces
https://codeforces.com/contest/1257/problem/D
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

int t, n, m, a[N], p[N], s[N], mxp[N];
int arb[4*N];

void update(int nod, int st, int dr, int idx, int val){
    if (st == dr){
        arb[nod] = val;
        return;
    }
    int mid = (st + dr) >> 1;
    if (idx <= mid) update(L, st, mid, idx, val);
    else update(R, mid+1, dr, idx, val);
    arb[nod] = smax(arb[L], arb[R]);
}

int get(int nod, int st, int dr, int l, int r){
    if (st >= l && dr <= r) return arb[nod];
    int mid = (st + dr) >> 1;
    int left = 0, right = 0;
    if (l <= mid) left = get(L, st, mid, l, r);
    if (r > mid) right = get(R, mid+1, dr, l, r);
    return smax(left, right);
}

bool check(int to, int from){
    int resist = to - from + 1;
    int potere = get(1, 1, n, from, to);
    return (mxp[resist] >= potere);
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> t;
    while (t--){
        int k = 0;
        cin >> n;
        for (int i=1; i<=n; i++){
            cin >> a[i];
            update(1, 1, n, i, a[i]);
        }
        cin >> m;
        for (int i=1; i<=n+1; i++) mxp[i] = 0;
        for (int i=1; i<=m; i++){
            cin >> p[i] >> s[i];
            mxp[s[i]] = smax(mxp[s[i]], p[i]);
        }
        for (int i=n; i; i--) mxp[i] = smax(mxp[i], mxp[i+1]);
        //for (int i=1; i<=n; i++) cout << mxp[i] << ' ';
        //cout << '\n';
        int idx = 1;
        while (idx <= n){
            int st = idx, dr = n;
            //cout << st << ' ' << dr << '\n';
            while (st <= dr){
                //cout << st << ' ' << dr << '\n';
                int mid = (st + dr) >> 1;
                if (check(mid, idx)) st = mid + 1;
                else dr = mid - 1;
            }
            if (st == idx){
                k = -1;
                break;
            }
            else idx = st;
            k++;
        }
        cout << k << '\n';
        for (int i=1; i<=n; i++) update(1, 1, n, i, 0);
    }
    return 0;
}

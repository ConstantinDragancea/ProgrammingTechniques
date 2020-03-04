/*
Solves problem QTREE from SPOJ
https://www.spoj.com/problems/QTREE/
*/
#include <bits/stdc++.h>
using namespace std;
typedef pair <int,int> pii;

#define L (nod << 1)
#define R (L | 1)
#define N 10010
struct edge{
    int to, c, idx;
} mxc[N];
int n, t, k, cnt[N], chain[N], chainNo, h[4*N], sz[N], lvl[N], ord[N], edgePos[N], p[N], bgn[N];
vector <edge> v[N];

void update(int nod, int st, int dr, int idx, int val){
    if (st == dr){
        h[nod] = val;
        return;
    }
    int mid = (st + dr) >> 1;
    if (idx <= mid) update(L, st, mid, idx, val);
    else update(R, mid+1, dr, idx, val);
    h[nod] = max(h[L], h[R]);
}

int query(int nod, int st, int dr, int l, int r){
    if (st >= l && dr <= r) return h[nod];
    int mid = (st + dr) >> 1;
    int left = -1, right = -1;
    if (l <= mid) left = query(L, st, mid, l, r);
    if (r > mid) right = query(R, mid+1, dr, l, r);
    return max(left, right);
}

int dfs(int q, int pr){
    int mxto, mxidx, mx = -1, mxcost;
    sz[q] = 1;
    for (auto it: v[q])
        if (it.to != pr){
            int tt = dfs(it.to, q);
            sz[q] += tt;
            if (tt > mx) mx = tt, mxto = it.to, mxcost = it.c, mxidx = it.idx;
        }
    if (mx != -1) mxc[q] = {mxto, mxcost, mxidx};
    mxc[q] = {0, 0, 0};
    return sz[q];
}

void hld(int q, int pr, int lv, int edgeidx){
    chain[q] = chainNo; k++;
    ord[q] = ++cnt[chain[q]];
    lvl[chain[q]] = lv;
    edgePos[edgeidx] = k;
    if (ord[q] == 1) bgn[chain[q]] = k;
    if (mxc[q].to){
        update(1, 1, n, k+1, mxc[q].c);
        hld(mxc[q].to, q, lv, mxc[q].idx);
    }
    for (auto it: v[q])
        if (it.to != pr && it.to != mxc[q].to){
            p[++chainNo] = q;
            update(1, 1, n, k+1, it.c);
            hld(it.to, q, lv + 1, it.idx);
        }

}

int main(){
    //ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    ifstream cin ("qtree.in");
    cin >> t;
    while (t--){
        cin >> n;
        //reset
        k = 0; chainNo = 1;
        for (int i=0; i<=n; i++){
            v[i].clear();
            cnt[i] = p[i] = chain[i] = ord[i] = edgePos[i] = sz[i] = lvl[i] = bgn[i] = 0;
            mxc[i] = {0, 0, 0};
        }
        for (int i=1, x, y, z; i<n; i++){
            cin >> x >> y >> z;
            v[x].push_back({y, z, i});
            v[y].push_back({x, z, i});
        }

        dfs(1, 0);
        hld(1, 0, 1, 0);
        for (int i=1; i<n; i++) cout << i << ": " << edgePos[i] << "\n";
        //for (int i=1; i<=n; i++) cout << i << ": " << ord[i] << "\n";
        while(1){
            string s; int x, y;
            cin >> s;
            if (s[0] == 'D') break;
            cin >> x >> y;
            if (s[0] == 'C') update(1, 1, n, edgePos[x], y);
            else{
                int ans = 0;
                if (lvl[chain[x]] > lvl[chain[y]]) swap(x, y);
                while (lvl[chain[y]] > lvl[chain[x]]){
                    ans = max(ans, query(1, 1, n, bgn[chain[y]], bgn[chain[y]]+ord[y]-1));
                    y = p[chain[y]];
                }
                while (chain[x] != chain[y]){
                    ans = max(ans, query(1, 1, n, bgn[chain[y]], bgn[chain[y]]+ord[y]-1));
                    ans = max(ans, query(1, 1, n, bgn[chain[x]], bgn[chain[x]]+ord[x]-1));
                    y = p[chain[y]]; x = p[chain[x]];
                }
                if (ord[x] > ord[y]) swap(x, y);
                if (ord[x] != ord[y]) ans = max(ans, query(1, 1, n, ord[x] + 1, ord[y]));
                printf("%d\n", ans);
            }
        }
    }
    return 0;
}


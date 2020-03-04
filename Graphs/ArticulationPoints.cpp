/*
Solves problem SUBMERGE from SPOJ
https://www.spoj.com/problems/SUBMERGE/
*/
#include <bits/stdc++.h>
using namespace std;

int n, m, low[10010], viz[10010], k, cnt, ap[10010], ans;
vector <int> v[10010];

void dfs(int q, int pr){
    viz[q] = low[q] = ++k;
    for (auto it: v[q]){
        if (it == pr) continue;
        if (!viz[it]){
            if (q == 1) cnt++;
            dfs(it, q);
            low[q] = min(low[q], low[it]);
            if (low[it] >= viz[q]) ap[q]++;
        }
        else low[q] = min(low[q], viz[it]);
    }
}

int main(){
    cin >> n >> m;
    while (n && m){
        ans = cnt = 0;
        for (int i=1; i<=n; i++) viz[i] = low[i] = ap[i] = 0, v[i].erase(v[i].begin(), v[i].end());
        for (int i=1; i<=m; i++){
            int x, y;
            cin >> x >> y;
            v[x].push_back(y);
            v[y].push_back(x);
        }
        dfs(1,-1);
        ap[1] = cnt - 1;
        for (int i=1; i<=n; i++)
            if (ap[i]) ans++;
        cout << ans << "\n";
        cin >> n >> m;
    }
    return 0;
}

/*
Solves proble QTREE2 from SPOJ
https://www.spoj.com/problems/QTREE2/
*/
#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second
#define N 10010
int n, t, dp[16][N], lvl[N], c[16][N];
vector <pair<int,int> > v[N];

void dfs(int q){
    for (auto it: v[q])
        if (!lvl[it.fi]){
            lvl[it.fi] = lvl[q] + 1;
            dp[0][it.fi] = q;
            c[0][it.fi] = it.se;
            dfs(it.fi);
        }
}

void build(){
    for (int put=1; (1<<put) <= n; put++)
        for (int i=1; i<=n; i++){
            dp[put][i] = dp[put-1][dp[put-1][i]];
            c[put][i] = c[put-1][i] + c[put-1][dp[put-1][i]];
        }
}

int get(int x, int step){
    while (step > 0){
        int put = 0;
        while ((1<<(put+1)) <= step) put++;
        x = dp[put][x];
        step -= (1<<put);
    }
    return x;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //ifstream cin ("qtree2.in");
    cin >> t;
    while (t--){
        cin >> n;
        for (int i=1; i<=n; i++) v[i].clear(), lvl[i] = 0;
        for (int put=0; (1<<put) <= n; put++)
            for (int i=1; i<=n; i++) dp[put][i] = c[put][i] = 0;
        for (int i=1, x, y, z; i<n; i++){
            cin >> x >> y >> z;
            v[x].push_back({y, z});
            v[y].push_back({x, z});
        }
        lvl[1] = 1;
        dfs(1);
        build();
        while(1){
            string s; int x, y, kth;
            cin >> s;
            if (s[1] == 'O') break;
            cin >> x >> y;
            if (s[0] == 'D'){
                int ans = 0;
                if (lvl[x] > lvl[y]) swap(x, y);
                while (lvl[y] > lvl[x]){
                    int put = 0;
                    while (lvl[dp[put+1][y]] >= lvl[x]) put++;
                    ans += c[put][y]; y = dp[put][y];
                }
                while (x != y){
                    int put = 0;
                    while (dp[put+1][x] != dp[put+1][y]) put++;
                    ans += c[put][x] + c[put][y];
                    x = dp[put][x]; y = dp[put][y];
                }
                cout << ans << '\n';
            }
            else{
                cin >> kth;
                int Y = y, X = x;
                int st = 1, dr = 0;
                while (lvl[y] > lvl[x]){
                    int put = 0;
                    while (lvl[dp[put+1][y] ] >= lvl[x]) put++;
                    dr += (1<<put); y = dp[put][y];
                }
                while (lvl[x] > lvl[y]){
                    int put = 0;
                    while (lvl[dp[put+1][x]] >= lvl[y]) put++;
                    st += (1 << put);
                    x = dp[put][x];
                }
                while (x != y){
                    int put = 0;
                    while (dp[put+1][x] != dp[put+1][y]) put++;
                    st += (1 << put); dr += (1 << put);
                    x = dp[put][x]; y = dp[put][y];
                }
                if (kth > st) cout << get(Y, dr-(kth-st)) << '\n';
                else cout << get(X, kth-1) << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}

/*
Solves problem MIXTURES from Codeforces
https://www.spoj.com/problems/MIXTURES/
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 105
#define fi first
#define se second
int n, a[N];
pair <ll, ll> dp[N][N];

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    while (cin >> n){
        for (int i=1; i<=n; i++) cin >> dp[i][i].se;
        for (int l=1; l<n; l++)
            for (int i=1; i + l <= n; i++){
                dp[i][i+l].fi = 1e9;
                for (int j=i; j<i + l; j++)
                    if (dp[i][j].fi + dp[j+1][i+l].fi + (dp[i][j].se * dp[j+1][i+l].se) < dp[i][i+l].fi)
                        dp[i][i+l] = {dp[i][j].fi + dp[j+1][i+l].fi + (dp[i][j].se * dp[j+1][i+l].se), (dp[i][j].se + dp[j+1][i+l].se)%100};
            }
        cout << dp[1][n].fi << '\n';
    }
    return 0;
}


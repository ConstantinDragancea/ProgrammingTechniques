/*
Solves problem 1257E from Codeforces
https://codeforces.com/contest/1257/problem/E
The problem is reduced to finding the longest non-decreasing subsequence of an array containing only 1, 2 and 3
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

int k1, k2, k3;
int a[N];
int dp[5][N];

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> k1 >> k2 >> k3;
    for (int i=1, x; i<=k1; i++){
        cin >> x;
        a[x] = 1;
    }
    for (int i=1, x; i<=k2; i++){
        cin >> x;
        a[x] = 2;
    }
    for (int i=1, x; i<=k3; i++){
        cin >> x;
        a[x] = 3;
    }
    int n = k1 + k2 + k3;
    //for (int i=1; i<=n; i++) cout << a[i] << ' ';
    //cout << '\n';
    for (int i=1; i<=n; i++){
        dp[1][i] = dp[1][i-1] + (a[i] > 1);
        dp[2][i] = smin(dp[1][i-1], dp[2][i-1]) + (a[i] != 2);
        dp[3][i] = smin(smin(dp[1][i-1], dp[2][i-1]), dp[3][i-1]) + (a[i] != 3);
    }
    cout << smin(smin(dp[1][n], dp[2][n]), dp[3][n]);
    return 0;
}

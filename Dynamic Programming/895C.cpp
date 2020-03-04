/*
Solves problem 895C from Codeforces
https://codeforces.com/contest/895/problem/C
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
#define N 100100
#define mod 1000000007

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

int n, poss[80][10], a[N], ans, mask[80], dp[80][(1<<19)], pr[80], k;
bool u[100];

bool isSquare(int q){
    int lol = sqrt(q);
    return (lol * lol == q);
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n;
    for (int i=2; i<=70; i++){
        if (!u[i]) pr[k++] = i;
        for (int j=i+i; j<=70; j+=i) u[j] = 1;
    }
    for (int i=2; i<=70; i++){
        int idx = 0, x = i, cnt = 0;
        while (x > 1){
            while (x % pr[idx] == 0) x /= pr[idx], cnt++;
            if (cnt & 1) mask[i] += (1<<idx);
            idx++; cnt = 0;
        }
    }
    for (int i=1; i<=n; i++) cin >> a[i];
    for (int i=1; i<=n; i++){
        if (a[i] == 1){
            poss[a[i]][0] = (poss[a[i]][0] + poss[a[i]][0] + 1) % mod;
            //poss[a[i]][1] = (poss[a[i]][1] + poss[a[i]][1] + 1) % mod;
        }
        else{
            int aux = poss[a[i]][0];
            poss[a[i]][0] = (poss[a[i]][0] + poss[a[i]][1]) % mod;
            poss[a[i]][1] = (poss[a[i]][1] + aux + 1) % mod;
        }
    }
    dp[0][0] = 1;
    for (int i=1; i<=70; i++){
        for (int j=0; j<(1<<19); j++){
            dp[i][j] = (1LL * dp[i-1][j] * poss[i][0] + 1LL * dp[i-1][j ^ mask[i]] * poss[i][1]) % mod;
            dp[i][j] = (dp[i][j] + dp[i-1][j]) % mod;
        }
    }
    cout << dp[70][0] - 1;
    return 0;
}

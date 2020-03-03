/*
Solves problem 1257F from Codeforces
https://codeforces.com/contest/1257/problem/F
Using a Meet-in-the-middle approach and bruteforce half of a "number" since
2^15 is doable in the time limit, and use map to hash the vector.
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
#define N 200

const ld e = 2.71828182845904523536028747;
const ld PI = 3.14159265359;
const ll inf = (1LL<<62);
const int iinf = (1<<30);
//CLOCKS_PER_SEC

int n, a[N], b[N];
map <vector<int>, int> M;

int cnt_bits(int q){
    int cnt = 0;
    for (int i=0; i<30; i++)
        if (q & (1<<i)) cnt++;
    return cnt;
}

int main(){
    //mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n;
    for (int i=1, x; i<=n; i++){
        cin >> x;
        for (int j=0; j<15; j++)
            if ((1<<j) & x) a[i] |= (1<<j);
        for (int j=15; j<30; j++)
            if ((1<<j) & x) b[i] |= (1<<j);
    }
    for (int i=0; i < (1<<15); i++){
        vector <int> v;
        int mn = (1<<30);
        for (int j=1; j<=n; j++){
            int aux = cnt_bits(a[j] ^ i);
            mn = smin(mn, aux);
            v.push_back(aux);
        }
        for (auto &it: v)
            it -= mn;
        M[v] = i;
    }
    for (int i=0; i < (1<<15); i++){
        int mx = -1;
        vector <int> v, w;
        for (int j=1; j<=n; j++){
            int aux = cnt_bits(b[j] ^ (i << 15));
            mx = smax(mx, aux);
            v.push_back(aux);
        }
        for (auto &it: v)
            w.push_back(mx - it);
        if (!M[w]) continue;
        rc(((i<<15) | M[w]));
    }
    rc(-1);
    return 0;
}

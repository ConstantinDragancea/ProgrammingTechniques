/*
Solves problem 1241C from Codeforces
https://codeforces.com/contest/1241/problem/C
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 200100

int n, ar[N], x, a, y, b, t;
ll k, gc;

bool cmp(int unu, int doi){
    return unu > doi;
}

bool check (int turns){
    ll curr = 0;
    int aux = turns / gc;
    int idx = 1;
    while (aux > 0){
        curr += 1LL * ar[idx++] * (x + y);
        aux--;
    }
    aux = turns / a - (turns / gc);
    while (aux > 0){
        curr += 1LL * ar[idx++] * x;
        aux--;
    }
    aux = turns / b - (turns / gc);
    while (aux > 0){
        curr += 1LL * ar[idx++] * y;
        aux--;
    }
    return (curr >= k);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> t;
    while (t--){
        cin >> n;
        for (int i=1; i<=n; i++) cin >> ar[i], ar[i] /= 100;
        sort(ar+1, ar+1+n, cmp);
        cin >> x >> a >> y >> b >> k;
        if (y > x) swap(x, y), swap(a, b);
        gc = __gcd(a, b); gc = 1LL * a * b / gc;
        //cout << "cmdm: " << gc << '\n';
        int st = 1, dr = n;
        while (st <= dr){
            //cout << st << ' ' << dr << '\n';
            int mid = (st + dr) >> 1;
            if (check(mid)) dr = mid - 1;
            else st = mid + 1;
        }
        cout << (st > n ? -1 : st) << '\n';
    }
    return 0;
}

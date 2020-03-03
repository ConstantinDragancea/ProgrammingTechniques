/*
Solves problem 1321E / 1320C from Codeforces
Using Segment Tree and Lazy Propagation
https://codeforces.com/problemset/problem/1320/C
I keep a max Segment Tree h describing an array of length 10^6, representing attack power.
Then, for a weapon with power pwr, h[node(pwr)] would represent the profit you can obtain by using the weapon,
by killing all the monsters with defense rating strictly less than pwr.
As such, the maximum overall will be stored at the top of the segment tree, h[1]
First, take every weapon with power - pwr and price - cost and I initialize the value at h[node(pwr)] with -cost
Then sort the armors in ascending order according to their defense value and the monsters in ascending
order according to their attack power.
Now, process the armor sets in order, so for an armor described by def and price:
   - for each monster with atk power less than def we add (using lazy propagation) to each position strictly
     greater than monster's defense the monsters profit.
   - the profit for this specific defense set will be h[1] - price
The maximum over all such profits will be the answer to the test
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define N 200100
#define dim 1000000
#define fi first
#define se second
#define L (nod << 1)
#define R (L | 1)

int h[4 * dim + 100];
int lazy[4 * dim + 100];
ll ans = -(1LL << 62);
int n, m, p;
pair <int,int> a[N];

struct lol{
    int def, atk, c;

    bool operator<(const lol &other)const{
        return atk < other.atk;
    }
} b[N];

void push(int nod, int st, int dr){
    if (!lazy[nod]) return;
    h[nod] += lazy[nod];
    if (st == dr){
        lazy[nod] = 0;
        return;
    }
    lazy[L] += lazy[nod];
    lazy[R] += lazy[nod];
    lazy[nod] = 0;
    return;
}

void update_range(int nod, int st, int dr, int l, int r, int val){
    if (l > r) return;
    if (st >= l && dr <= r){
        lazy[nod] += val;
        push(nod, st, dr);
        return;
    }
    push(nod, st, dr);
    int mid = (st + dr) >> 1;
    if (l <= mid) update_range(L, st, mid, l, r, val);
    else push(L, st, mid);
    if (r > mid) update_range(R, mid+1, dr, l, r, val);
    else push(R, mid+1, dr);
    h[nod] = max(h[L], h[R]);
}

void set_value(int nod, int st, int dr, int idx, int val){
    push(nod, st, dr);
    if (st == dr){
        //cout << nod << ' ' << st << ' ' << dr << ' ' << h[nod] << ' ';
        h[nod] = max(h[nod], val);
        //cout << h[nod] << '\n';
        lazy[nod] = 0;
        return;
    }
    int mid = (st + dr) >> 1;
    if (idx <= mid){
        set_value(L, st, mid, idx, val);
        push(R, mid+1, dr);
    }
    else{
        set_value(R, mid+1, dr, idx, val);
        push(L, st, mid);
    }
    h[nod] = max(h[L], h[R]);
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    //ifstream cin ("test.in");
    cin >> n >> m >> p;
    update_range(1, 1, dim, 1, dim, -(1 << 30));
    for (int i=1, x, y; i<=n; i++){
        cin >> x >> y;
        set_value(1, 1, dim, x, -y);
    }
    for (int i=1; i<=m; i++) cin >> a[i].fi >> a[i].se;
    sort(a+1, a+1+m);
    for (int i=1; i<=p; i++)
        cin >> b[i].def >> b[i].atk >> b[i].c;
    sort(b+1, b+1+p);
    int idx = 0;
    for (int i=1; i<=m; i++){
        while (idx < p && b[idx + 1].atk < a[i].fi){
            idx++;
            update_range(1, 1, dim, b[idx].def + 1, dim, b[idx].c);
        }
        ans = max(ans, 1LL * h[1] - a[i].se);
    }
    cout << ans;
    return 0;
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return max(a, b); }
ll e() { return -1e18; }
ll mapping(ll a, ll b) { return a + b; }
ll composition(ll a, ll b) { return a + b; }
ll id() { return 0; }
ll l, r;

bool gr(ll x) { return x <= r; }
bool gl(ll x) { return x < l; }

int main() {
  ll N, Q;
  cin >> N;
  vi v(5e5 + 10);
  ranges::iota(v, 0LL);

  lazy_segtree<ll, op, e, ll, mapping, composition, id> seg(v);

  rep(_, N) {
    cin >> l >> r;
    ll rr = seg.max_right<gr>(0);
    ll rl = seg.max_right<gl>(0);

    if (rl < rr) {
      seg.apply(rl, rr, 1);
    }
  }

  cin >> Q;
  while (Q--) {
    ll x;
    cin >> x;
    cout << seg.get(x) << "\n";
  }
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return a + b; }
ll e() { return 1e18; }
ll mapping(ll a, ll b) { return min(a, b); }
ll composition(ll a, ll b) { return min(a, b); }
ll id() { return 1e18; }

int main() {
  ll N, Q;
  cin >> N >> Q;
  vi S(N), T(N), X(N), D(Q);
  rep(i, N) cin >> S[i] >> T[i] >> X[i];
  input(D);

  lazy_segtree<ll, op, e, ll, mapping, composition, id> seg(Q);

  rep(i, N) {
    ll l = ranges::lower_bound(D, S[i] - X[i]) - D.begin(),
       r = ranges::lower_bound(D, T[i] - X[i]) - D.begin();

    if (l < Q) {
      seg.apply(l, r, X[i]);
    }
  }

  rep(i, Q) {
    ll res = seg.get(i);
    cout << (res == 1e18 ? -1 : res) << "\n";
  }
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using S = tuple<ll, ll, ll>;

S op(S a, S b) {
  ll ax, ay, az, bx, by, bz;
  tie(ax, ay, az) = a;
  tie(bx, by, bz) = b;
  return {min(ax, bx), min(ay, by), min(az, bz)};
}
S e() { return {1e18, 1e18, 1e18}; }
S id() { return {-1e18, -1e18, 1e18}; }
S mapping(S l, S r) {
  if (l == id()) {
    return r;
  } else {
    return l;
  }
}
S composition(S l, S r) {
  if (l == id()) {
    return r;
  } else {
    return l;
  }
}

int main() {
  ll H, W;
  cin >> H >> W;

  VC<S> L(W);
  rep(i, W) L[i] = {i, -i, 0};
  lazy_segtree<S, op, e, S, mapping, composition, id> seg(L);

  rep(i, H) {
    ll a, b, l, r, _;
    cin >> a >> b;
    a--;
    b--;

    tie(l, r, _) = seg.prod(a, b + 1);

    if (b + 1 < W) {
      ll x, y, z, nz;
      tie(x, y, z) = seg.get(b + 1);
      nz = b + 1 + r;
      if (nz < z) {
        seg.set(b + 1, S{nz + b + 1, nz - (b + 1), nz});
      }
    }

    seg.apply(a, b + 1, e());

    ll res;
    tie(_, _, res) = seg.all_prod();

    if (res == (ll)1e18) {
      cout << -1;
    } else {
      cout << res + i + 1;
    }
    cout << "\n";
  }
}

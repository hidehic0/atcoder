#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll INF = 1e18;

pii op(pii a, pii b) {
  return mp(max(a.first, b.first), max(a.second, b.second));
}
pii e() { return mp(-INF, -INF); }

int main() {
  ll N;
  cin >> N;
  vi P(N);
  rep(i, N) {
    ll p;
    cin >> p;
    P[p - 1] = i;
  }

  segtree<pii, op, e> seg(N);

  ll ans = 0;
  si S;

  rrep(i, N) {
    S.emplace(P[i]);
    if (i + 1 == N) {
      seg.set(P[i], mp(-P[i], P[i]));
      continue;
    }

    ll cur = 0;
    ll l = -INF, r = -INF;
    auto it = S.lower_bound(P[i]);

    if (it != S.begin()) {
      l = seg.prod(*prev(it), P[i]).first + P[i];
    }
    if (next(it) != S.end()) {
      r = seg.prod(P[i], *next(it) + 1).second - P[i];
    }

    cur = max(l, r);

    chmax(ans, cur);
    seg.set(P[i], mp(cur - P[i], cur + P[i]));
  }

  cout << ans << "\n";
}

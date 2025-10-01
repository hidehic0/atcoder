#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using S = pii;
S op(S a, S b) { return S{max(a.first, b.first), max(a.second, b.second)}; }
S e() { return S{LONG_LONG_MIN, LONG_LONG_MIN}; }

int main() {
  ll N, C, M;
  cin >> N >> C >> M;
  vector<S> v;
  rep(i, N) { v.emplace_back(LONG_LONG_MIN, LONG_LONG_MIN); }
  v[0] = S{-C * N, 0};

  segtree<S, op, e> seg(v);

  rep(_, M) {
    ll t, p;
    cin >> t >> p;
    t--;

    ll ml = seg.prod(0, t).first, mr = seg.prod(t, N).second;

    ml += (C * (N - t));
    mr += (C * (t));

    ll ma = max(ml, mr) + p;
    auto [cl, cr] = seg.get(t);

    chmax(cl, ma - (C * (N - t)));
    chmax(cr, ma - (C * (t)));

    seg.set(t, S{cl, cr});
  }

  ll ans = 0;

  rep(i, N) { chmax(ans, seg.get(i).first + (C * (N - i))); }

  cout << ans << "\n";
}

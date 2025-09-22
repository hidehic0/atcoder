#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return max(a, b); }
ll e() { return 0; }
ll id() { return 0; }
ll mapping(ll f, ll x) { return f + x; }
ll composition(ll f, ll g) { return f + g; }

int main() {
  ll N, D, W;
  cin >> N >> D >> W;

  vector<vi> L(5 * pow(10, 5) + 100);

  rep(_, N) {
    ll t, x;
    cin >> t >> x;
    L[t].emplace_back(x);
  }

  ll f = 0, ans = 0;
  lazy_segtree<ll, op, e, ll, mapping, composition, id> seg(2 * pow(10, 5) +
                                                            100);

  rep(i, 5 * pow(10, 5) + 100) {
    if (i - D >= 0) {
      for (ll x : L[i - D]) {
        seg.apply(max(0LL, x - W), x, -1);
      }
    }
    for (ll x : L[i]) {
      seg.apply(max(0LL, x - W), x, 1);
    }

    chmax(ans, seg.all_prod());
  }

  cout << ans << "\n";
}

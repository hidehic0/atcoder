#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using mint = atcoder::modint998244353;
#include <atcoder/segtree>
using namespace atcoder;

#include "segtree/dualsegtree.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include "utils/compress.hpp"

ll op(ll a, ll b) { return max(a, b); }
ll e() { return -1e18; }

int main() {
  ll N;
  cin >> N;
  vpii L(N);
  vi X(N);
  cin >> L;
  sort(all(L));
  rep(i, N) X[i] = L[i].first;

  auto D = compress_1d(X);
  segtree<ll, op, e> seg(N);
  rep(i, N) seg.set(i, i);

  rrep(i, N) {
    ll bis = lower_bound(all(X), L[i].first + L[i].second) - X.begin();
    seg.set(i, seg.prod(i, bis));
  }

  VC<mint> dp(N + 1, 0);
  dp[0] = 1;

  rep(i, N) {
    dp[i + 1] += dp[i];
    dp[seg.get(i) + 1] += dp[i];
  }

  cout << dp.back().val() << "\n";
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, X, K, INF = pow(10, 16);
  cin >> N >> X >> K;

  vector<vector<pair<ll, ll>>> D(N);

  rep(_, N) {
    ll p, u, c;
    cin >> p >> u >> c;
    D[c - 1].emplace_back(p, u);
  }

  vi dp(X + 1, -INF);
  dp[0] = 0;

  rep(i, N) {
    if (D[i].empty()) {
      continue;
    }

    vector ndp(X + 1, vi(2, -INF));
    rep(x, X + 1) { ndp[x][0] = dp[x]; }

    for (auto item : D[i]) {
      auto [p, u] = item;

      for (ll x = X - p; x >= 0; x--) {
        chmax(ndp[x + p][1], ndp[x][0] + u + K);
        chmax(ndp[x + p][1], ndp[x][1] + u);
      }
    }

    rep(x, X + 1) {
      chmax(ndp[x][0], ndp[x][1]);
      chmax(dp[x], ndp[x][0]);
    }
  }

  ll ans = -INF;
  rep(x, X + 1) chmax(ans, dp[x]);

  cout << ans << "\n";
}

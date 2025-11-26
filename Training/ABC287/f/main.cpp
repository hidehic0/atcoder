#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N;
vvi G;

using mint = modint998244353;

VC<VC<mint>> dfs(ll cur, ll par) {
  VC<VC<mint>> dp(2, VC<mint>(2, 0));
  dp[0][0] = 1;
  dp[1][1] = 1;

  rep(ind, G[cur].size()) {
    ll nxt = G[cur][ind];
    if (nxt == par)
      continue;

    auto cdp = dfs(nxt, cur);
    VC<VC<mint>> ndp(dp.size() + cdp.size() - 1, VC<mint>(2, 0));

    rep(i, dp.size()) {
      rep(k, cdp.size()) {
        ndp[i + k][0] += dp[i][0] * (cdp[k][0] + cdp[k][1]);
        ndp[i + k][1] += dp[i][1] * cdp[k][0];

        if (i + k > 0)
          ndp[i + k - 1][1] += dp[i][1] * cdp[k][1];
      }
    }

    dp = ndp;
  }

  return dp;
}

int main() {
  cin >> N;
  G.resize(N);

  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  auto dp = dfs(0, -1);

  REP(i, 1, N + 1) cout << (dp[i][0] + dp[i][1]).val() << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N;
vvi G;
constexpr ll MOD = 1e9 + 7;

vvi dfs(ll cur, ll par = -1) {
  vvvi L;
  ll M = 1;
  for (ll nxt : G[cur]) {
    if (nxt != par) {
      L.emplace_back(dfs(nxt, cur));
      M += L.back().size() - 1;
    }
  }

  vvi dp(2, vi(3, 0));
  dp[0][0] = 1;
  dp[1][2] = 1;

  rep(n, L.size()) {
    vvi l = L[n];
    vvi next(dp.size() + l.size() - 1, vi(3, 0));
    rep(i, dp.size()) {
      rep(k, l.size()) {
        if (i + k + 1 < next.size()) {
          next[i + k + 1][1] += dp[i][0] * l[k][2];
          next[i + k + 1][1] %= MOD;
          next[i + k + 1][2] += dp[i][2] * l[k][0];
          next[i + k + 1][2] %= MOD;
        }
        if (i + k < next.size()) {
          next[i + k][0] += dp[i][0] * (l[k][0] + l[k][1]);
          next[i + k][0] %= MOD;
          next[i + k][1] += dp[i][1] * (l[k][2] + l[k][0] + l[k][1]);
          next[i + k][1] %= MOD;
          next[i + k][2] += dp[i][2] * (l[k][1] + l[k][2]);
          next[i + k][2] %= MOD;
        }
      }
    }

    dp = next;
  }

  return dp;
}

int main() {
  cin >> N;
  G.resize(N);

  rep(_, N - 1) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  auto dp = dfs(0);

  rep(i, N + 1) { cout << (dp[i][0] + dp[i][1] + dp[i][2]) % MOD << "\n"; }
}

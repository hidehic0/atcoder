#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, K;
vi A;
vvi G;

vvi dfs(ll cur, ll par = -1) {
  vvi dp(K + 1, vi(3, -1e18));
  dp[0][0] = 0;

  for (ll nxt : G[cur]) {
    if (nxt == par)
      continue;

    auto ch = dfs(nxt, cur);

    rrep(i, K + 1) {
      rrep(k, K + 1) {
        if (i + k <= K) {
          chmax(dp[i + k][1], max({
                                  dp[i][0] + ch[k][1] + A[cur],
                                  dp[i][1] + ch[k][0],
                                  dp[i][1] + ch[k][1],
                              }));
          chmax(dp[i + k][0], dp[i][0] + ch[k][0]);
          chmax(dp[i + k][2], dp[i][2] + max(ch[k][1], ch[k][0]));
        }

        if (i + k - 1 <= K && i + k - 1 >= 0) {
          chmax(dp[i + k - 1][2], dp[i][1] + ch[k][1]);
        }
      }
    }
  }

  REP(k, 1, K + 1) chmax(dp[k][1], dp[k - 1][0] + A[cur]);
  rep(k, K + 1) chmax(dp[k][0], dp[k][2]);

  return dp;
}

int main() {
  cin >> N >> K;
  A.resize(N);
  cin >> A;
  G.resize(N);

  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  auto dp = dfs(0);

  ll ans = -1e18;
  rep(a, K + 1) { rep(b, 3) chmax(ans, dp[a][b]); }

  cout << ans << "\n";
}

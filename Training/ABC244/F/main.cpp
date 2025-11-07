#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;

  vvi G(N), dp(1 << N, vi(N, 1e18));
  queue<pii> Q;

  rep(i, N) {
    dp[1 << i][i] = 1;
    Q.emplace(1 << i, i);
  }

  rep(_, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;

    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  while (!Q.empty()) {
    ll bit, cur;
    tie(bit, cur) = Q.front();
    Q.pop();

    for (ll nxt : G[cur]) {
      ll nb = bit ^ (1 << nxt);

      if (dp[nb][nxt] > dp[bit][cur] + 1) {
        dp[nb][nxt] = dp[bit][cur] + 1;
        Q.emplace(nb, nxt);
      }
    }
  }

  ll ans = 0;

  REP(bit, 1, 1 << N) { ans += *min_element(all(dp[bit])); }

  cout << ans << "\n";
}

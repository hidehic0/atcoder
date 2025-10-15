#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll S, T, M;
  cin >> S >> T >> M;

  vvi G(S + T), dp(T, vi(T, -1));

  rep(_, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;

    G[u].emplace_back(v);
  }

  rep(i, S) {
    rep(a, G[i].size()) {
      REP(b, 0, G[i].size()) {
        ll x = G[i][a], y = G[i][b];
        if (dp[x - S][y - S] != -1 && x != y) {
          cout << dp[x - S][y - S] + 1 dms x + 1 dms i + 1 dms y + 1 << "\n";
          return 0;
        }

        dp[x - S][y - S] = i;
      }
    }
  }

  cout << "-1\n";
}

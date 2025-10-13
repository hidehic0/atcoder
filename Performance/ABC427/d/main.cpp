#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll T;
  cin >> T;

  rep(_, T) {
    ll N, M, K;
    string S, T = "AB";
    cin >> N >> M >> K >> S;
    vvi G(N);

    rep(_, M) {
      ll u, v;
      cin >> u >> v;
      u--;
      v--;

      G[u].emplace_back(v);
    }

    vector dp(N, vi(K * 2 + 1, -1));

    auto dfs = [&](ll cur, ll cnt, auto self) -> ll {
      if (dp[cur][cnt] != -1) {
        return dp[cur][cnt];
      }
      if (cnt == K * 2) {
        if (T[cnt % 2] == S[cur]) {
          return dp[cur][cnt] = cnt % 2;
        } else {
          return dp[cur][cnt] = (cnt % 2) ^ 1;
        }
      }

      rep(i, G[cur].size()) {
        ll nxt = G[cur][i];
        if (self(nxt, cnt + 1, self) == cnt % 2) {
          return dp[cur][cnt] = cnt % 2;
        }
      }

      return dp[cur][cnt] = (cnt % 2) ^ 1;
    };

    dfs(0, 0, dfs);

    if (dp[0][0] == 0) {
      cout << "Alice" << "\n";
    } else {
      cout << "Bob" << "\n";
    }
  }
}

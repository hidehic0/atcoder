// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll inf = 1LL << 50;

ll f(vector<vector<ll>> &dp, vector<ll> l) {
  ll prev = 0;

  rep(u, dp[0].size()) {
    rep(v, dp[0].size()) {
      if (u != v) {
        prev += dp[u][v] == inf ? 0 : dp[u][v];
      }
    }
  }

  for (auto k : l) {
    rep(u, dp[0].size()) {
      rep(v, dp[0].size()) { chmin(dp[u][v], dp[u][k] + dp[k][v]); }
    }
  }
  ll n = 0;

  rep(u, dp[0].size()) {
    rep(v, dp[0].size()) {
      if (u != v) {
        n += dp[u][v] == inf ? 0 : dp[u][v];
      }
    }
  }

  return n - prev;
}

int main() {
  ll N, M, K, T;

  cin >> N >> M;

  vector<vector<ll>> dp(N, vector<ll>(N, inf));

  ll a, b, c;
  rep(_, M) {
    cin >> a >> b >> c;
    a--;
    b--;

    chmin(dp[a][b], c);
    chmin(dp[b][a], c);
  }

  cin >> K >> T;
  vector<ll> D;

  rep(_, K) {
    ll d;
    cin >> d;
    d--;
    D.emplace_back(d);
  }

  for (auto u : D) {
    for (auto v : D) {
      chmin(dp[u][v], T);
      chmin(dp[v][u], T);
    }
  }

  ll ans = 0;

  rep(k, N) {
    rep(u, N) {
      rep(v, N) { chmin(dp[u][v], dp[u][k] + dp[k][v]); }
    }
  }

  rep(u, N) {
    rep(v, N) {
      if (dp[u][v] != inf && u != v) {
        ans += dp[u][v];
      }
    }
  }

  ll Q;
  cin >> Q;

  while (Q--) {
    ll t;
    cin >> t;

    if (t == 1) {
      cin >> a >> b >> c;
      a--;
      b--;
      ll p = dp[a][b];
      chmin(dp[a][b], c);
      chmin(dp[b][a], c);
      ans -= (p - c) * 2;

      ans += f(dp, {a, b});
    } else if (t == 2) {
      ll x;
      cin >> x;
      x--;

      vector<ll> l;
      l.emplace_back(x);

      for (auto i : D) {
        if (dp[x][i] > T || dp[i][x] > T) {
          ll p = dp[x][i];
          dp[x][i] = T;
          dp[i][x] = T;
          ans += p == inf ? T : (T - p);
          l.emplace_back(i);
        }
      }

      ans += f(dp, l);

      D.emplace_back(x);

    } else {
      cout << ans << "\n";
    }
  }
}

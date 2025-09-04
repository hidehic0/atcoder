#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, K, T = 0;
  cin >> N >> M >> K;
  vi A(M);

  rep(i, M) {
    cin >> A[i];
    A[i]--;
  }

  map<pair<ll, ll>, ll> D;
  vector<pair<ll, ll>> E(N - 1);
  vector G(N, vector<pair<ll, ll>>());

  rep(i, N - 1) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;

    if (u > v)
      swap(u, v);

    E[i] = mp(u, v);
    G[u].push_back(mp(v, i));
    G[v].push_back(mp(u, i));
  }

  auto dfs = [&](ll u, ll v) {
    vi used(N, -1);
    used[u] = u;

    queue<ll> Q;
    Q.push(u);

    while (!Q.empty()) {
      ll cur = Q.front();
      Q.pop();

      for (auto [nxt, ind] : G[cur]) {
        if (used[nxt] == -1) {
          used[nxt] = cur;
          Q.push(nxt);
        }
      }
    }

    ll cur = v;

    while (cur != u) {
      D[mp(min(used[cur], cur), max(used[cur], cur))]++;
      T++;
      cur = used[cur];
    }
  };

  rep(i, M - 1) { dfs(A[i], A[i + 1]); }

  vector dp(T + 1, modint998244353(0));
  dp[0] = 1;

  rep(i, N - 1) {
    ll u, v;
    tie(u, v) = E[i];

    ll cnt;
    if (D.count(mp(u, v)))
      cnt = D[mp(u, v)];
    else
      cnt = 0;

    for (ll k = T; k >= 0; k--) {
      if (k + cnt <= T) {
        dp[k + cnt] += dp[k];
      }
    }
  }

  modint998244353 ans = 0;

  rep(r, T + 1) {
    ll b = T - r;

    if (b <= T && r - b == K) {
      ans += dp[r];
    }
  }

  cout << ans.val() << "\n";
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, INF = pow(10, 17);
  cin >> N >> M;

  vector G(N + 1, vi());

  rep(_, M) {
    ll a, b;
    cin >> a >> b;
    G[a].emplace_back(b);
    if (a != 0) {
      G[b].emplace_back(a);
    }
  }

  auto get_dists = [&](ll st) {
    vi used(N + 1, INF);
    used[st] = 0;
    queue<ll> Q;
    Q.push(st);

    while (!Q.empty()) {
      auto cur = Q.front();
      Q.pop();

      for (auto nxt : G[cur]) {
        if (chmin(used[nxt], used[cur] + 1))
          Q.push(nxt);
      }
    }

    return used;
  };

  vi dist_s = get_dists(1);
  vi dist_g = get_dists(N);

  ll p_s_cost = INF;
  ll p_g_cost = INF;

  for (auto t : G[0]) {
    chmin(p_s_cost, dist_s[t]);
    chmin(p_g_cost, dist_g[t]);
  }

  vi ans(N, INF);

  rep(i, N) {
    chmin(ans[i], dist_s[N]);
    chmin(ans[i], p_s_cost + 1 + dist_g[i + 1]);
    chmin(ans[i], p_g_cost + 1 + dist_s[i + 1]);
    chmin(ans[i], p_g_cost + p_s_cost + 2);
  }

  rep(i, N) cout << (ans[i] == INF ? -1 : ans[i]) << (i + 1 == N ? "\n" : " ");
}

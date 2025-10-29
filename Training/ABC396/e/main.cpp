#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;

  vvpii G(N);

  rep(i, M) {
    ll x, y, z;
    input(x, y, z);
    x--;
    y--;

    G[x].emplace_back(y, z);
    G[y].emplace_back(x, z);
  };

  vi ans(N, 0), memo(N, -1);
  vb used(N);

  auto bfs = [&](ll start, ll fv) {
    ll res = 0;

    queue<ll> Q;
    Q.emplace(start);
    si vis;
    vis.emplace(start);
    memo[start] = 0;

    while (!Q.empty()) {
      ll cur = Q.front();
      used[cur] = true;
      Q.pop();

      for (auto [nxt, w] : G[cur]) {
        if (vis.count(nxt) == 0) {
          memo[nxt] = memo[cur] ^ w;
          used[nxt] = true;
          vis.emplace(nxt);
          Q.emplace(nxt);
        } else {
          if (memo[nxt] != (memo[cur] ^ w)) {
            vis.clear();
            return vis;
          }
        }
      }
    }

    return vis;
  };

  rep(i, N) {
    if (used[i])
      continue;

    si vis = bfs(i, 0);

    if (vis.size() == 0) {
      cout << -1 << "\n";
      return 0;
    }

    rep(k, 30) {
      ll cnt = 0;
      for (ll p : vis) {
        if ((memo[p] >> k) & 1)
          cnt++;
      }

      for (ll p : vis) {
        if (vis.size() - cnt < cnt) {
          memo[p] ^= 1 << k;
        }

        if ((memo[p] >> k) & 1) {
          ans[p] += 1 << k;
        }
      }
    }
  }

  out(ans);
}

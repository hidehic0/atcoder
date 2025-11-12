#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, ans = 0;
vi D;
vvpii G;

ll dfs(ll cur, ll par = -1) {
  vi L;

  for (auto [nxt, w] : G[cur]) {
    if (nxt == par)
      continue;

    ll t = dfs(nxt, cur);

    if (w >= t && w - t >= 0 && D[nxt] >= 1) {
      L.emplace_back(w - t);
    }
  }

  sort(all(L), greater<ll>{});

  ll res = 0;

  rep(i, L.size()) {
    if (i < D[cur] - 1) {
      ans += L[i];
    } else if (i == D[cur] - 1) {
      ans += L[i];
      res = L[i];
    }
  }

  return res;
}

int main() {
  cin >> N;
  D = vi(N);
  input(D);
  G = vvpii(N);

  rep(_, N - 1) {
    ll u, v, w;
    cin >> u >> v >> w;
    u--;
    v--;

    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }

  dfs(0);

  cout << ans << "\n";
}

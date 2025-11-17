#include <bits/stdc++.h>
using namespace std;

#include "data-structure/unionfind.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, K;
  cin >> N >> M >> K;
  map<ll, vpii> E;

  rep(_, M) {
    ll u, v, w;
    cin >> u >> v >> w;

    E[w].emplace_back(u - 1, v - 1);
  }

  UnionFind UF(N);
  ll ans = 0;

  vi cnt_a(N), cnt_b(N);

  rep(_, K) {
    ll a;
    cin >> a;
    cnt_a[a - 1]++;
  }
  rep(_, K) {
    ll b;
    cin >> b;
    cnt_b[b - 1]++;
  }

  for (auto [w, l] : E) {
    for (auto [u, v] : l) {
      if (UF.same(u, v))
        continue;

      u = UF.leader(u);
      v = UF.leader(v);

      UF.merge(u, v);

      if (UF.leader(u) == v)
        swap(u, v);

      cnt_a[u] += cnt_a[v];
      cnt_b[u] += cnt_b[v];

      ll mi = min(cnt_a[u], cnt_b[u]);
      ans += mi * w;
      cnt_a[u] -= mi;
      cnt_b[u] -= mi;
    }
  }

  cout << ans << "\n";
}

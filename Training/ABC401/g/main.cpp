#include <bits/stdc++.h>
using namespace std;
#include <atcoder/maxflow>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using T = tuple<ld, ll, ll>;

int main() {
  ll N;
  cin >> N;

  VC<pair<ld, ld>> S(N), G(N);
  cin >> S >> G;

  VC<T> edges;

  rep(i, N) {
    rep(k, N) {
      ld dx = S[i].first - G[k].first, dy = S[i].second - G[k].second;
      edges.emplace_back(sqrt(dx * dx + dy * dy), i, k);
    }
  }

  sort(all(edges));

  ll left = -1, right = N * N;

  while (right - left > 1) {
    ll mid = (right + left) / 2;

    mf_graph<ll> G(N * 2 + 2);

    rep(i, mid + 1) {
      auto [_, x, y] = edges[i];
      G.add_edge(x, y + N, 1);
    }

    rep(i, N) {
      G.add_edge(N * 2, i, 1);
      G.add_edge(i + N, N * 2 + 1, 1);
    }

    if (G.flow(N * 2, N * 2 + 1) == N)
      right = mid;
    else
      left = mid;
  }

  cout << fixed << setprecision(10) << get<0>(edges[right]) << "\n";
}

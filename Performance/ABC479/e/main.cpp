/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

#include "segtree/dualsegtree.hpp"
#include "tree/heavy_light_decomposition.hpp"

int main() {
  ll N;
  in(N);

  VC G(N, VC<int>());
  VC<pii> E(N - 1);

  for (auto &[a, b] : E) {
    in(a, b), --a, --b;

    G[a].emplace_back(b), G[b].emplace_back(a);
  }

  vi ans(N + 1);

  HeavyLightDecomposition hld(G);

  for (auto [i, p] : E | views::enumerate) {
    auto [a, b] = p;

    if (hld.depth[a] > hld.depth[b])
      swap(a, b);

    ll bs = hld.size[b];
    ll as = N - bs;

    dump(as, bs);

    if (as < bs) {
      ans[hld.in[b]] += i + 1;
      ans[hld.out[b]] -= i + 1;
    } else {
      ans[0] += i + 1;
      ans[N] -= i + 1;

      ans[hld.in[b]] -= i + 1;
      ans[hld.out[b]] += i + 1;
    }
  }

  rep(i, N) ans[i + 1] += ans[i];

  dump(hld.rev, hld.in, hld.out);

  rep(i, N) cout << ans[hld.in[i]] << (i + 1 == N ? "\n" : " ");
}

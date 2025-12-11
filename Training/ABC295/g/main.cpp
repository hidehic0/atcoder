#include <bits/stdc++.h>
using namespace std;

#include "data-structure/unionfind.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  cin >> N;
  vi P(N), res(N, 0);
  REP(i, 1, N) {
    cin >> P[i];
    P[i]--;
    res[i] = i;
  }
  cin >> Q;

  UnionFind UF(N);

  while (Q--) {
    ll t;
    cin >> t;
    if (t == 1) {
      ll u, v;
      cin >> u >> v;
      u--;
      v--;

      vi l = {res[UF.leader(v)]};
      u = res[UF.leader(u)];

      while (UF.leader(u) != UF.leader(v)) {
        l.emplace_back(res[UF.leader(u)]);
        u = P[u];
      }

      for (ll w : l)
        UF.merge(v, w);

      res[UF.leader(v)] = *ranges::min_element(l);
    } else {
      ll x;
      cin >> x;
      cout << res[UF.leader(x - 1)] + 1 << "\n";
    }
  }
}

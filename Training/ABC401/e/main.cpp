#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;

  vvi G(N);

  rep(_, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;

    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  si S, T;
  dsu UF(N);
  rep(i, G[0].size()) S.emplace(G[0][i]);

  REP(i, 1, N) {
    cout << (UF.size(0) == i ? (ll)S.size() : -1) << "\n";
    bool flag = false;
    S.erase(i);

    for (ll v : G[i]) {
      flag |= UF.same(0, v);

      if (v > i) {
        S.emplace(v);
      }
    }

    for (ll v : G[i]) {
      if (v <= i) {
        UF.merge(v, i);
      }
    }

    if (!flag) {
      T.emplace(i);
    } else {
      UF.merge(0, i);
    }
  }

  cout << (UF.size(0) == N ? (ll)S.size() : -1) << "\n";
}

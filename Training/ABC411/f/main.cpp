#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, Q;
  cin >> N >> M;
  vector<pii> E;
  vector<si> G(N), L(N);
  vi par(N);

  rep(_, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;
    E.emplace_back(u, v);

    G[u].emplace(v);
    G[v].emplace(u);
  }

  rep(i, N) {
    L[i].emplace(i);
    par[i] = i;
  }

  cin >> Q;
  ll cur = M;

  while (Q--) {
    ll x;
    cin >> x;
    x--;

    ll u = par[E[x].first], v = par[E[x].second];

    if (u == v) {
      cout << cur << "\n";
      continue;
    }

    if (L[u].size() + G[u].size() < L[v].size() + G[v].size()) {
      swap(u, v);
    }

    for (auto c : L[v]) {
      par[c] = u;
      L[u].emplace(c);
    }
    L[v].clear();

    for (auto c : G[v]) {
      if (c == u) {
        G[u].erase(v);
        cur--;
        continue;
      } else if (G[u].contains(c)) {
        cur--;
      } else {
        G[u].emplace(c);
        G[c].emplace(u);
      }

      G[c].erase(v);
    }

    G[v].clear();

    cout << cur << "\n";
  }
}

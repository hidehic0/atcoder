#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"
ll N, M;
vi A;
vvi G;

bool check(ll x) {
  vi cos(N, 0);
  vector<bool> used(N, false);
  vector<pii> PQ;

  rep(u, N) {
    for (ll v : G[u])
      cos[u] += A[v];

    if (cos[u] <= x) {
      used[u] = true;
      PQ.emplace_back(cos[u], u);
    }
  }

  while (!PQ.empty()) {
    ll c, u;
    tie(c, u) = PQ.back();
    PQ.pop_back();

    for (ll v : G[u]) {
      if (!used[v]) {
        cos[v] -= A[u];
        if (cos[v] <= x) {
          used[v] = true;
          PQ.emplace_back(cos[v], v);
        }
      }
    }
  }

  return count(all(used), true) == N;
}

int main() {
  cin >> N >> M;
  A.resize(N);

  rep(i, N) cin >> A[i];
  G.resize(N);

  rep(_, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;

    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  ll left = -1, right = 3e14;

  while (right - left > 1) {
    ll mid = (left + right) / 2;

    if (check(mid)) {
      right = mid;
    } else {
      left = mid;
    }
  }

  cout << left + 1 << "\n";
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;

  vi X(N + 1, 0), D(N + 1, 0);

  rep(i, N) cin >> X[i + 1];

  set<pii> L;
  L.emplace(0, 0);

  ll cur = 0;

  REP(i, 1, N + 1) {
    ll nd = X[i] - prev(L.lower_bound(mp(X[i], i)))->first;

    if (prev(L.end())->first > X[i]) {
      chmin(nd, L.lower_bound(mp(X[i], i))->first - X[i]);
    }

    cur += nd;
    D[i] = nd;

    L.emplace(X[i], i);

    auto it = L.lower_bound(mp(X[i], i));

    auto [lx, li] = *prev(it);

    if (li < i) {
      if (X[i] - lx < D[li] || D[li] == 0) {
        cur -= D[li];
        D[li] = X[i] - lx;
        cur += D[li];
      }
    }

    if (next(it) != L.end()) {
      auto [rx, ri] = *next(it);

      if (rx - X[i] < D[ri] || D[ri] == 0) {
        cur -= D[ri];
        D[ri] = rx - X[i];
        cur += D[ri];
      }
    }

    cout << cur << "\n";
  }
}

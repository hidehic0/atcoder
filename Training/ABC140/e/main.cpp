#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree.hpp>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  vi P(N);
  input(P);

  mii D;
  rep(i, N) { D[P[i]] = i + 1; }

  si S;
  S.emplace(0);
  S.emplace(N + 1);

  ll ans = 0;

  RREP(i, 1, N + 1) {
    S.emplace(D[i]);
    auto it = S.lower_bound(D[i]);
    ll a = *prev(it), b = *next(it), c = 0, d = N + 1;

    if (next(S.begin()) != it) {
      c = *prev(prev(it));
    }

    if (next(next(it)) != S.end()) {
      d = *next(next(it));
    }

    ans += i * (((a - c) * (b - D[i])) + ((d - b) * (D[i] - a)));
  }

  out(ans);
}

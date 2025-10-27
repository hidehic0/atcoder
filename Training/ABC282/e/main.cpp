#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "data-structure/unionfind.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  input(N, M);
  vi A(N);
  input(A);

  using mint = modint;
  mint::set_mod(M);
  vector<pair<mint, pii>> E;

  rep(i, N) {
    REP(k, i + 1, N) {
      mint w = mint{A[i]}.pow(A[k]) + mint{A[k]}.pow(A[i]);
      E.emplace_back(w, mp(i, k));
    }
  }

  sort(all(E), [](pair<mint, pii> a, pair<mint, pii> b) {
    return a.first.val() > b.first.val();
  });

  ll ans = 0;
  UnionFind UF(N);

  for (auto [w, e] : E) {
    auto [a, b] = e;

    if (!UF.same(a, b)) {
      UF.merge(a, b);
      ans += w.val();
    }
  }

  cout << ans << "\n";
}

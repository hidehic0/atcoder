#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  cin >> N >> Q;
  vi H(N), L(N), ans(Q, -1);
  rep(i, N) {
    cin >> H[i];
    H[i]--;
  }

  segtree<ll, [](ll a, ll b) -> ll { return max(a, b); },
          []() -> ll { return 0; }>
      seg1(N);

  rep(i, N) {
    L[i] = seg1.prod(H[i], N);
    seg1.set(H[i], i);
  }

  vvpii D(N);

  rep(i, Q) {
    ll l, r;
    cin >> l >> r;
    l--;
    r--;

    D[r].emplace_back(l, i);
  }

  segtree<ll, [](ll a, ll b) -> ll { return a + b; }, []() -> ll { return 0; }>
      seg2(N);

  rrep(i, N) {
    for (auto [l, ind] : D[i])
      ans[ind] = seg2.prod(0, l + 1);

    seg2.set(L[i], seg2.get(L[i]) + 1);
  }

  rep(i, Q) { cout << ans[i] << "\n"; }
}

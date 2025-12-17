#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using namespace atcoder;

using mint = modint1000000007;

#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include "tree/rerooting.hpp"

mint P[(int)2e5 + 10]{1}, PINV[(int)2e5 + 10]{1};
using T = pair<mint, mint>;

T merge(T a, T b) {
  return {P[(a.second + b.second).val()] * PINV[a.second.val()] *
              PINV[b.second.val()] * a.first * b.first,
          a.second + b.second};
}
T add_root(T a, int u) { return {a.first, a.second + 1}; }

int main() {
  ll N;
  cin >> N;

  VC<VC<int>> G(N);
  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  REP(i, 1, 2e5 + 9) {
    P[i] = P[i - 1] * i;
    PINV[i] = P[i].inv();
  }

  auto res = rerooting(G, merge, add_root, T{1, 0});

  rep(i, N) { cout << res[i].first.val() << "\n"; }
}

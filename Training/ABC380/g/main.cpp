#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using mint = modint998244353;
using S = pair<mint, mint>;

S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
S e() { return {0, 0}; }
S mapping(mint l, S r) { return {r.first + l * r.second, r.second}; }
mint composition(mint l, mint r) { return l + r; }
mint id() { return 0; }

int main() {
  ll N, K;
  cin >> N >> K;
  vi P(N);
  cin >> P;
  rep(i, N) P[i]--;

  lazy_segtree<S, op, e, mint, mapping, composition, id> seg(N);
  fenwick_tree<mint> ft(N);

  mint base = 0;

  rep(i, N) {
    base += ft.sum(P[i], N);
    ft.add(P[i], 1);
  }

  VC<mint> F(2e5 + 100, 1), FINV(2e5 + 100, 1);
  REP(i, 1, 2e5 + 100) {
    F[i] = F[i - 1] * i;
    FINV[i] = F[i].inv();
  }

  mint nxt_inversions = F[K] * F[K] * FINV[2] * FINV[max(K - 2, 0LL)] * FINV[2];
  if (K == 1)
    nxt_inversions = 0;

  // REP(i, 1, K) { nxt_inversions += mint{i} * mint{2}.pow(i - 1); }
  mint ans = 0;
  rrep(i, N) {
    seg.set(P[i], {0, 1});

    if (i + K < N) {
      seg.set(P[i + K], e());
    }

    if (P[i] > 0)
      seg.apply(0, P[i], 1);

    if (i + K > N) {
      continue;
    }

    ans += (base - seg.all_prod().first) * F[K] + nxt_inversions;
  }

  ans /= mint{N - K + 1} * F[K];

  cout << ans.val() << "\n";
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;
#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using S = pair<mint, mint>;

S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
S e() { return {0, 0}; }

int main() {
  ll N;
  cin >> N;
  vi P(N);
  cin >> P;

  rep(i, N) P[i]--;
  segtree<S, op, e> seg1(N), seg2(N);

  rep(i, N) {
    S u = seg1.prod(0, P[i] + 1);
    seg1.set(P[i], {u.first + u.second + seg2.prod(0, P[i] + 1).first, 1});

    if (P[i] == N - 1)
      continue;

    seg2.set(P[i],
             {seg1.prod(P[i] + 1, N).first + seg2.prod(P[i], N).first, 0});
  }

  cout << seg2.all_prod().first.val() << "\n";
}

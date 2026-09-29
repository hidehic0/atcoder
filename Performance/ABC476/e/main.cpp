/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

struct S {
  pii x, y;
};

S op(S a, S b) { return {min(a.x, b.x), max(a.y, b.y)}; }
S e() { return {mp(1e18, 1e18), mp(-1e18, -1e18)}; }

int main() {
  ll N, M;
  in(N, M);
  vi P(N);
  in(P);

  VC<S> v;

  rep(i, N) v.emplace_back(mp(P[i], i), mp(P[i], i));

  segtree<S, op, e> seg(v);

  while (M--) {
    ll l, r;
    in(l, r);

    auto [x, y] = seg.prod(l - 1, r);

    seg.set(x.second, {mp(y.first, x.second), mp(y.first, x.second)});
    seg.set(y.second, {mp(x.first, y.second), mp(x.first, y.second)});
  }

  vi NP;

  rep(i, N) NP.emplace_back(seg.get(i).x.first);

  out(NP);
}

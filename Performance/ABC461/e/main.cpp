/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

#include "segtree/dualsegtree.hpp"

int main() {
  ll N, Q;
  in(N, Q);

  vi R(N, -1), C(N, -1);
  DualSegmentTree<ll, [](ll a, ll b) { return a + b; },
                  []() { return 1LL << 50; }>
      seg1(Q + 1), seg2(Q + 1);
  seg2.apply(0, 1, -seg2.get(0));
  ll ans = 0;

  for (ll qi = 1; qi <= Q; qi++) {
    ll t, i;
    in(t, i), t--, i--;

    if (t == 0) {
      if (R[i] == -1) {
        ans += N;
        seg2.apply(0, qi, 1);
      } else {
        ans += seg1.get(R[i]);
        seg2.apply(R[i], qi, 1);
      }

      R[i] = qi;

      seg1.apply(qi, qi + 1, -seg1.get(qi));
    } else {
      if (C[i] == -1) {
        ans -= seg2.get(0);
        seg1.apply(0, qi, 1);
      } else {
        ans -= seg2.get(C[i]);
        seg1.apply(C[i], qi, 1);
      }

      seg2.apply(qi, qi + 1, -seg2.get(qi));
      C[i] = qi;
    }

    out(ans);
  }
}

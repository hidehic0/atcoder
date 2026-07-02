/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

#include "data-structure/2d-segtree.hpp"

int main() {
  ll H, W, Q;
  in(H, W, Q);

  VC<char> T = {'A'};
  SegmentTree2D<ll, [](ll a, ll b) { return max(a, b); }, []() { return 0; }>
      seg(VC(H, vi(W, 0)));

  rep(i, 1, Q + 1) {
    ll r, c;
    char x;
    in(r, c, x);

    T.emplace_back(char(x));
    seg.set(r - 1, c - 1, i);
  }

  rep(i, H) {
    string res;
    rep(k, W) res += T[seg.prod(i, H, k, W)];

    out(res);
  }
}

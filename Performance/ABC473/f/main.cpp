/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

struct Tp {
  int m, r;
};

constexpr int INF = 1e9;

Tp op(Tp a, Tp b) {
  if (a.m == -INF)
    return b;
  if (b.m == -INF)
    return a;

  return {min(a.m, a.r + b.m), a.r + b.r};
};
Tp e() { return {-INF, -INF}; }

int main() {
  int N;
  in(N);
  string S;
  in(S);

  array<Tp, 2> L = {Tp{1, 1}, Tp{-1, -1}};

  segtree<Tp, op, e> seg(N);
  rep(i, N) seg.set(i, L[S[i] - 'A']);
  int Q;
  in(Q);

  while (Q--) {
    int t;
    in(t);

    if (t == 1) {
      int i;
      char c;
      in(i, c), --i;

      seg.set(i, L[(S[i] = c) - 'A']);
    } else {
      int l, r;
      in(l, r);

      dump(seg.prod(l - 1, r).m);
      if (seg.prod(l - 1, r).m >= 0)
        out("Yes");
      else
        out("No");
    }
  }
}

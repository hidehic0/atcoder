/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

ll INF = 1e18;

vvi mat_mul(vvi a, vvi b) {
  vvi res(a.size(), vi(b[0].size(), INF));

  rep(i, a.size()) {
    rep(j, b[0].size()) {
      rep(k, b.size()) { chmin(res[i][j], a[i][k] + b[k][j]); }
    }
  }

  return res;
}

vvi e() { return {{INF, 0}, {0, 0}}; }
vvi op(vvi a, vvi b) {
  if (a == e())
    return b;
  if (b == e())
    return a;
  return mat_mul(a, b);
}

void solve() {
  ll N, K;
  in(N, K);
  vi A(N);
  in(A);

  VC V(N, VC(2, vi(2, INF)));

  rep(i, N) {
    V[i][1][0] = A[i];
    V[i][1][1] = A[i];
    V[i][0][1] = 0;
  }
  dump(V);

  ll ans = INF;
  segtree<vvi, op, e> seg(V);
  vvi T(2, vi(1, 1e18));
  T[0][0] = 0;

  rep(i, N - K + 1) {
    auto P = seg.prod(i, min(i + K, N));
    chmin(ans, mat_mul(P, T)[1][0]);
    if (i + K < N) {
      P = mat_mul(P, V[i + K]);
      chmin(ans, mat_mul(P, T)[1][0]);
    }
  }

  out(ans);
}

int main() {
  ll T;
  in(T);
  while (T--) {
    solve();
  }
}

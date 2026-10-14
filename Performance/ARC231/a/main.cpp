/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

#include "geometry/convexhulltrick.hpp"

constexpr int W = 500;

void solve() {
  int N;
  in(N);

  vvi dp(W, vi(W, 1e18)), cos(W, vi(W, 1e18));
  cos[0][0] = 0;

  {
    ll x = 0;

    ConvexHullTrick<false, ll> cht;

    rep(y, W) if (cos[x][y] != 1e18) cht.add_func(-2 * y, cos[x][y] + y * y);
    rep(y, W) dp[x][y] = cht.query(y) + y * y;
  }

  ll zs = 0;
  ll ans = 0;

  rep(_, N) {
    int x, y, z;
    in(x, y, z);

    zs += z;

    ll m = 1e18;

    rep(px, W) chmin(m, ll(px - x) * ll(px - x) + dp[px][y] - z);

    chmin(ans, m);

    if (chmin(cos[x][y], m)) {
      ConvexHullTrick<false, ll> cht;

      rep(y, W) if (cos[x][y] != 1e18) cht.add_func(-2 * y, cos[x][y] + y * y);
      rep(y, W) dp[x][y] = cht.query(y) + y * y;
    }
  }

  out(ans + zs);
}

int main() {
  ll T;
  in(T);

  while (T--)
    solve();
}

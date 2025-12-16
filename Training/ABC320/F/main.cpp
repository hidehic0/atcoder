#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, H;
  cin >> N >> H;
  vi X(N), P(N), F(N);
  cin >> X;
  rep(i, N - 1) cin >> P[i] >> F[i];

  vvi dp(H + 1, vi(H + 1, 1e18));
  dp[H][0] = 0;

  rep(i, N) {
    vvi ndp(H + 1, vi(H + 1, 1e18));
    ll dis = X[i] - (i - 1 == -1 ? 0 : X[i - 1]);

    rep(a, H + 1) {
      rep(b, H + 1) {
        if (a - dis >= 0 && b + dis <= H)
          chmin(ndp[a - dis][b + dis], dp[a][b]);
        if (i == 0)
          continue;
        if (min(a + F[i - 1], H) - dis >= 0 && b + dis <= H)
          chmin(ndp[min(a + F[i - 1], H) - dis][b + dis], dp[a][b] + P[i - 1]);
        if (a - dis >= 0 && max(b - F[i - 1], 0LL) + dis <= H)
          chmin(ndp[a - dis][max(b - F[i - 1], 0LL) + dis],
                dp[a][b] + P[i - 1]);
      }
    }

    dp = ndp;
  }

  ll ans = LONG_LONG_MAX;
  rep(a, H + 1) { rep(b, a + 1) chmin(ans, dp[a][b]); }

  cout << (ans == 1e18 ? -1 : ans) << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, X;
  cin >> N >> X;
  vi A(N);
  input(A);

  ll ans = LONG_LONG_MAX;

  REP(n, 1, N + 1) {
    vvi dp(n + 1, vi(n, -1e18));
    dp[0][X % n] = 0;

    rep(i, N) {
      rrep(k, n) {
        rep(m, n) {
          chmax(dp[k + 1][((m - A[i]) % n + n) % n], dp[k][m] + A[i]);
        }
      }
    }

    if (dp[n][0] >= 0) {
      chmin(ans, (X - dp[n][0]) / n);
    }
  }

  cout << ans << "\n";
}

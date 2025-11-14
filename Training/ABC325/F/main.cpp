#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, AL, AC, AK, BL, BC, BK;
  cin >> N;
  vi D(N);
  input(D);
  input(AL, AC, AK, BL, BC, BK);

  vvi dp(N + 1, vi(AK + 1, 1e18));
  dp[0][0] = 0;

  rep(i, N) {
    rep(k, AK + 1) {
      rep(l, AK - k + 1) {
        if (k + l <= AK) {
          chmin(dp[i + 1][k + l],
                dp[i][k] + ceil_div(max(D[i] - l * AL, 0LL), BL));
        }
      }
    }
  }

  ll ans = 1e18;

  rep(k, AK + 1) {
    if (dp.back()[k] <= BK) {
      chmin(ans, dp.back()[k] * BC + k * AC);
    }
  }

  cout << (ans == 1e18 ? -1 : ans) << "\n";
}

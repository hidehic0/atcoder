#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using mint = modint;

int main() {
  ll N, P;
  cin >> N >> P;

  mint::set_mod(P);

  VC dp(N, VC(N, VC(2, mint{0})));

  dp[0][0][1] = 1;
  dp[0][1][0] = 1;

  rep(i, N - 1) {
    rep(k, N) {
      if (k + 1 < N) {
        dp[i + 1][k + 1][1] += dp[i][k][1] * 3;
        dp[i + 1][k + 1][0] += dp[i][k][0];
      }

      if (k + 2 < N) {
        dp[i + 1][k + 2][0] += dp[i][k][1] * 2;
      }

      dp[i + 1][k][1] += dp[i][k][1] + dp[i][k][0];
    }
  }

  REP(i, 1, N) { cout << dp[N - 1][i][1].val() << (i + 1 == N ? "\n" : " "); }
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, INF = pow(10, 17);
  cin >> N >> M;
  vi A(N);
  rep(i, N) cin >> A[i];

  vector dp(N + 1, vector(M + 1, vi(2, INF)));
  dp[0][0][0] = 0;

  rep(i, N) {
    rep(k, M + 1) {
      if (k + A[i] <= M) {
        chmin(dp[i + 1][k + A[i]][0], dp[i][k][0]);
        chmin(dp[i + 1][k + A[i]][0], dp[i][k][1]);
      }

      chmin(dp[i + 1][k][1], dp[i][k][0] + 1);
      chmin(dp[i + 1][k][1], dp[i][k][1]);
    }
  }

  REP(i, 1, M + 1) {
    cout << (min(dp[N][i][0], dp[N][i][1]) == INF
                 ? -1
                 : min(dp[N][i][0], dp[N][i][1]))
         << "\n";
  }
}

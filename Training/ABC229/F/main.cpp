#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  vi A(N), B(N);
  input(A);
  input(B);

  vvvi dp(N, vvi(2, vi(2, 1e18)));

  dp[0][0][1] = 0;
  dp[0][0][0] = A[0];

  REP(i, 1, N) {
    dp[i][0][0] =
        min(dp[i - 1][1][0] + A[i], dp[i - 1][0][0] + A[i] + B[i - 1]);
    dp[i][1][0] = min(dp[i - 1][0][0], dp[i - 1][1][0] + B[i - 1]);
    dp[i][0][1] = min(dp[i - 1][1][1], dp[i - 1][0][1] + B[i - 1]);
    dp[i][1][1] =
        min(dp[i - 1][0][1] + A[i], dp[i - 1][1][1] + A[i] + B[i - 1]);
  }

  cout << min({dp.back()[1][1], dp.back()[0][1] + B.back(),
               dp.back()[0][0] + B.back(), dp.back()[1][0]})
       << "\n";
}

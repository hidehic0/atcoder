#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, S, MOD = 998244353;
  cin >> N >> S;
  vi A(N);
  cin >> A;
  ll ans = 0;

  vvi dp(N + 1, vi(S + 1, -1));
  dp[0][0] = 0;

  rep(i, N) {
    rep(k, S + 1) {
      if (dp[i][k] == -1)
        continue;
      if (dp[i + 1][k] == -1)
        dp[i + 1][k] = 0;

      dp[i + 1][k] += dp[i][k];
      dp[i + 1][k] %= MOD;

      if (k + A[i] <= S) {
        if (k + A[i] == S) {
          ans += dp[i][k] * (N - i);
          ans %= MOD;
        }
        if (A[i] == S) {
          ans += (i + 1) * (N - i);
          ans %= MOD;
        }

        if (dp[i + 1][k + A[i]] == -1)
          dp[i + 1][k + A[i]] = 0;

        dp[i + 1][k + A[i]] += dp[i][k];
        dp[i + 1][k + A[i]] %= MOD;

        if (k == 0) {
          dp[i + 1][A[i]] += i + 1;
          dp[i + 1][A[i]] %= MOD;
        }
      }
    }
  }
  cout << ans << "\n";
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  string S;
  cin >> S;

  vi dp(2, 0);

  ll ans = 0;

  rep(i, N) {
    ans += dp[1];
    vi new_dp(2, 0);

    if (S[i] == *"0") {
      new_dp[1] = dp[0] + dp[1];
      new_dp[0] = 1;
    } else {
      new_dp[1] = 1 + dp[0];
      new_dp[0] = dp[1];
    }

    dp = new_dp;
  }

  cout << ans + dp[1] << "\n";
}

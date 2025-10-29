#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using mint = atcoder::modint1000000007;

int main() {
  ll N;
  cin >> N;

  vi A(N);
  input(A);

  ll cur = 0;
  VC<VC<mint>> dp(N + 1, VC<mint>(N + 1, 0)), memo(N + 1, VC<mint>(N + 1, 0));
  dp[0][0] = 1;

  rep(i, N) {
    rep(k, N) { memo[k + 1][cur % (k + 1)] += dp[i][k]; }
    cur += A[i];

    rep(k, N) { dp[i + 1][k + 1] += memo[k + 1][cur % (k + 1)]; }
  }

  mint ans = 0;

  rep(k, N + 1) { ans += dp[N][k]; }

  cout << ans.val() << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, X, Y;
  cin >> N >> X >> Y;
  vi A(N), B(N);
  cin >> A >> B;

  vi dp(1 << N, 5e18);
  dp[0] = 0;

  rep(bit, (1 << N) - 1) {
    if (dp[bit] == 5e18)
      continue;

    ll M = popcount((unsigned int)bit);

    rep(i, N) {
      if ((bit >> i) & 1)
        continue;

      ll dis = 0;
      rep(k, i) {
        if (!((bit >> k) & 1))
          dis++;
      }

      chmin(dp[bit | (1 << i)], dp[bit] + dis * Y + abs(A[i] - B[M]) * X);
    }
  }

  cout << dp.back() << "\n";
}

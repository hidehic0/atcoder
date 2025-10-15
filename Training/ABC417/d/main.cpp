#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  cin >> N;

  vi P(N), A(N), B(N), PB(N + 1, 0);
  rep(i, N) cin >> P[i] >> A[i] >> B[i];
  rep(i, N) PB[i + 1] += B[i] + PB[i];

  vector dp(N + 1, vi(1100, 0));

  rrep(i, N) {
    rep(k, 1100) {
      dp[i][k] = P[i] < k ? dp[i + 1][k - min((ll)k, B[i])] - min((ll)k, B[i])
                          : dp[i + 1][k + A[i]] + A[i];
    }
  }

  cin >> Q;

  while (Q--) {
    ll x;
    cin >> x;

    if (x < 1100) {
      cout << dp[0][x] + x;
    } else {
      auto it = lower_bound(all(PB), x - 1099);

      if (it == PB.end()) {
        cout << x - PB.back();
      } else {
        ll ind = it - PB.begin();
        cout << dp[ind][x - *it] + x - *it;
      }
    }

    cout << "\n";
  }

  return 0;
}

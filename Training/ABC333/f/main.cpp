#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using mint = modint998244353;

int main() {
  ll N;
  cin >> N;

  VC<mint> P(N + 5, 1), PINV(N + 5, 1);

  REP(i, 1, N + 4) {
    P[i] = P[i - 1] * i;
    PINV[i] = P[i].inv();
  }

  VC<mint> dp(N + 2);
  dp[0] = 1;

  REP(i, 1, N + 1) {
    mint p = PINV[2].pow(i + 1) * ((1 - PINV[2].pow(i + 1)).inv());
    REP(k, 1, i + 1) { dp[i] += P[i] * PINV[k] * PINV[i - k] * dp[i - k]; }
    dp[i] *= p;
  }

  rep(i, N) {
    mint res = 0;
    rep(k, i + 1) { res += P[i] * PINV[k] * PINV[i - k] * dp[N - (i - k) - 1]; }
    res /= mint{2}.pow(i);

    cout << res.val() << (i + 1 == N ? "\n" : " ");
  }
}

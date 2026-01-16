#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using mint = atcoder::modint998244353;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll R, G, B, K;
  cin >> R >> G >> B >> K;

  VC<mint> P(3e6 + 10, 1), PINV(3e6 + 10, 1);

  REP(i, 1, 3e6 + 10) {
    P[i] *= P[i - 1] * i;
    PINV[i] = P[i].inv();
  }

  mint ans = P[R + B] * PINV[R] * PINV[B];
  ans *= P[R] * PINV[R - K] * PINV[K];
  ll n = B + K + (G - K), k = G - K;
  ans *= P[n] * PINV[k] * PINV[n - k];

  cout << ans.val() << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll A, B;
  cin >> A >> B;

  vi P = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29,
          31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

  vi dp(1 << 20, 0);
  dp[0] = 1;

  for (ll i = A; i <= B; i++) {
    ll nb = 0;

    rep(k, 20) {
      if (i % P[k] == 0) {
        nb |= 1 << k;
      }
    }

    rrep(bit, (1 << 20)) {
      if ((bit & nb) == 0) {
        dp[bit | nb] += dp[bit];
      }
    }
  }

  cout << reduce(all(dp), 0, [](ll a, ll b) { return a + b; }) << "\n";
}

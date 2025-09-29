#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using mint = modint998244353;

int main() {
  ll N;
  string T;
  cin >> N >> T;

  vector<mint> dp(1 << N, 0);
  dp[0] += 1;

  rep(bit, 1 << N) {
    char back = 'A';
    rep(i, N) {
      if (!(bit & (1 << i))) {
        if (back != T[i]) {
          dp[bit | (1 << i)] += dp[bit];
        }
        back = T[i];
      }
    }
  }

  cout << dp[(1 << N) - 1].val() << "\n";
}

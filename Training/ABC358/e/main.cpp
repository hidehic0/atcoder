#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll K, N = 26;
  input(K);
  vi C(N);
  input(C);

  vector<modint998244353> F = {modint998244353{1}, modint998244353{1}}, FINV;

  REP(i, 2, 1003) { F.emplace_back(*prev(F.end()) * i); }
  rep(i, F.size()) { FINV.emplace_back(F[i].inv()); }

  vector dp(N + 1, vector(K + 1, modint998244353{0}));
  dp[0][0] += 1;

  rep(i, N) {
    rep(k, K + 1) {
      dp[i + 1][k] += dp[i][k];

      REP(c, 1, C[i] + 1) {
        if (k + c <= K) {
          modint998244353 b = F[k + c] * FINV[c] * FINV[k];
          dp[i + 1][k + c] += dp[i][k] * b;
        }
      }
    }
  }

  modint998244353 ans = -1;

  rep(i, K + 1) { ans += dp[N][i]; }

  cout << ans.val() << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

constexpr int mod = 998244353;

int dp[302][302][302]{0};

int main() {
  int N, K;
  cin >> N >> K;

  VC<pair<int, int>> L(N);
  rep(i, N) cin >> L[i].first;
  rep(i, N) cin >> L[i].second;

  sort(all(L));
  dp[0][0][N] = 1;

  int q;

  rep(i, N) {
    q = L[i].second;
    q--;
    rep(k, K + 1) {
      rep(mq, N + 1) {
        if (mq > q) {
          dp[i + 1][k + 1][mq] += dp[i][k][mq];
          dp[i + 1][k + 1][mq] %= mod;
        }

        dp[i + 1][k][min(mq, q)] += dp[i][k][mq];
        dp[i + 1][k][min(mq, q)] %= mod;
      }
    }
  }

  int ans = 0;

  rep(i, N + 1) {
    ans += dp[N][K][i];
    ans %= mod;
  }

  cout << ans << "\n";
}

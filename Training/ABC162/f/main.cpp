#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll solve(vi A, ll x, ll y) {
  vvvi dp(A.size(), vvi(2, vi(3, -1e18)));
  dp[0][1][2] = A[0];

  rep(i, A.size()) {
    rep(a, 2) {
      rep(b, 3) {
        if (i - 2 >= 0) {
          chmax(dp[i][a][b], dp[i - 2][a][b] + A[i]);
        }
        if (i - 3 >= 0 && b >= 1)
          chmax(dp[i][a][b - 1], dp[i - 3][a][b] + A[i]);
        if (i - 4 >= 0 && a >= 1)
          chmax(dp[i][a - 1][b], dp[i - 4][a][b] + A[i]);
      }
    }
  }

  ll res = -1e18;

  if (x == 1 && y == 2 && A.size() >= 3) {
    chmax(res, dp[A.size() - 3][1][2]);
  }

  rep(a, 2) {
    rep(b, 3) {
      if (a == 1 && 2 - b <= x && A.size() != 1) {
        chmax(res, dp[A.size() - 2][a][b]);
      }
      if (x == 1 && y == 2 && a == 1 && b == 2)
        continue;
      if ((1 - a) + 2 - b <= y) {
        chmax(res, dp[A.size() - 1][a][b]);
      }
    }
  }

  return res;
}

int main() {
  ll N;
  cin >> N;
  vi A(N);
  cin >> A;

  ll ans = solve(A, N % 2, N % 2 + 1);

  if (N % 2 != 0) {
    reverse(all(A));
    A.pop_back();
    reverse(all(A));
    chmax(ans, solve(A, 0, 1));
    reverse(all(A));
    A.pop_back();
    reverse(all(A));
    chmax(ans, solve(A, 0, 0));
  } else {
    reverse(all(A));
    A.pop_back();
    reverse(all(A));
    chmax(ans, solve(A, 0, 0));
  }

  cout << ans << "\n";
}

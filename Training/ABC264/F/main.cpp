#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll f(ll color, ll r_rev, ll c_rev) {
  return ((1 << 2) * color) + ((1 << 1) * r_rev) + c_rev;
}

int main() {
  ll H, W;
  cin >> H >> W;
  vi R(H), C(W);
  cin >> R >> C;

  vvi A(H, vi(W));
  rep(i, H) {
    string S;
    cin >> S;

    rep(k, W) A[i][k] = S[k] - '0';
  }

  vvvi dp(H, vvi(W, vi(8, 1e18)));

  if (A[0][0] == 0) {
    dp[0][0][f(0, 0, 0)] = 0;
    dp[0][0][f(0, 1, 1)] = R[0] + C[0];
    dp[0][0][f(1, 1, 0)] = R[0];
    dp[0][0][f(1, 0, 1)] = C[0];
  } else {
    dp[0][0][f(1, 0, 0)] = 0;
    dp[0][0][f(1, 1, 1)] = R[0] + C[0];
    dp[0][0][f(0, 1, 0)] = R[0];
    dp[0][0][f(0, 0, 1)] = C[0];
  }

  rep(x, H) {
    rep(y, W) {
      rep(state, 8) {
        ll color = (state >> 2) & 1, r_rev = (state >> 1) & 1,
           c_rev = state & 1;

        if (x + 1 < H) {
          if (color != (A[x + 1][y] ^ c_rev)) {
            chmin(dp[x + 1][y][f(color, 1, c_rev)], dp[x][y][state] + R[x + 1]);
          } else {
            chmin(dp[x + 1][y][f(color, 0, c_rev)], dp[x][y][state]);
          }
        }

        if (y + 1 < W) {
          if (color != (A[x][y + 1] ^ r_rev)) {
            chmin(dp[x][y + 1][f(color, r_rev, 1)], dp[x][y][state] + C[y + 1]);
          } else {
            chmin(dp[x][y + 1][f(color, r_rev, 0)], dp[x][y][state]);
          }
        }
      }
    }
  }

  cout << *min_element(all(dp.back().back())) << "\n";
}

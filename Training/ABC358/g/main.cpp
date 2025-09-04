#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

int main() {
  ll H, W, K, sx, sy, INF = pow(10, 17);
  cin >> H >> W >> K >> sx >> sy;
  sx--;
  sy--;

  vector A(H, vi(W));

  rep(x, H) rep(y, W) cin >> A[x][y];

  vector dp(H, vector(W, vi(H * W + 1, -INF)));
  dp[sx][sy][0] = 0;

  rep(dist, H * W) {
    rep(x, H) {
      rep(y, W) {
        rep(i, 4) {
          ll nx = x + dx[i], ny = y + dy[i];
          if (0 <= nx && nx < H && 0 <= ny && ny < W) {
            chmax(dp[nx][ny][dist + 1], dp[x][y][dist] + A[nx][ny]);
          }
        }
      }
    }
  }

  ll ans = 0;

  rep(x, H) {
    rep(y, W) {
      rep(dist, min(H * W, K) + 1) {
        if (dp[x][y][dist] >= 0) {
          chmax(ans, dp[x][y][dist] + (K - dist) * A[x][y]);
        }
      }
    }
  }

  cout << ans << endl;
}

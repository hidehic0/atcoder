#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, INF = 5e17;
  cin >> N;

  vector P(N, vi(N)), R(N, vi(N - 1)), D(N - 1, vi(N));
  vector<vector<pii>> dp(N, vector<pii>(N, {INF, INF}));
  dp[0][0] = {0, 0};

  rep(i, N) rep(k, N) cin >> P[i][k];
  rep(i, N) rep(k, N - 1) cin >> R[i][k];
  rep(i, N - 1) rep(k, N) cin >> D[i][k];

  rep(i, N) {
    rep(k, N) {
      ll cnt, m;
      tie(cnt, m) = dp[i][k];
      m *= -1;
      vvi dis(N, vi(N, INF));

      dis[i][k] = 0;

      REP(nx, i, N) {
        REP(ny, k, N) {
          if (nx == i && ny == k)
            continue;

          if (nx - 1 >= 0) {
            chmin(dis[nx][ny], dis[nx - 1][ny] + D[nx - 1][ny]);
          }

          if (ny - 1 >= 0) {
            chmin(dis[nx][ny], dis[nx][ny - 1] + R[nx][ny - 1]);
          }

          ll pc = max(dis[nx][ny] - m + P[i][k] - 1, 0LL) / P[i][k];
          ll nm = (pc * P[i][k]) + m - dis[nx][ny];

          chmin(dp[nx][ny], mp(pc + cnt + nx - i + ny - k, -nm));
        }
      }
    }
  }

  cout << dp[N - 1][N - 1].first << "\n";
}

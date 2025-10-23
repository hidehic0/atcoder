#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

double dis(pair<double, double> a, pair<double, double> b) {
  auto [ax, ay] = a;
  auto [bx, by] = b;
  return sqrt(pow(ax - bx, 2) + pow(ay - by, 2));
}

int main() {
  ll N, M;
  cin >> N >> M;
  vector<pii> A(N), B(M);

  rep(i, N) cin >> A[i].first >> A[i].second;
  rep(i, M) cin >> B[i].first >> B[i].second;

  vvf dp(1 << (N + M), vf(N + M, 1e17));

  rep(i, N) dp[1 << i][i] =
      sqrt((double)pow(A[i].first, 2) + pow(A[i].second, 2));
  rep(i, M) dp[1 << (N + i)][N + i] =
      sqrt((double)pow(B[i].first, 2) + pow(B[i].second, 2));

  rep(bit, 1 << (N + M)) {
    rep(cur, N + M) {
      if (!((bit >> cur) & 1)) {
        continue;
      }

      ll speed = 1;
      rep(i, M) {
        if ((bit >> (i + N)) & 1)
          speed *= 2;
      }

      rep(nxt, N) {
        if ((bit >> nxt) & 1)
          continue;

        if (cur < N) {
          chmin(dp[bit | (1 << nxt)][nxt],
                dp[bit][cur] + (dis(A[cur], A[nxt]) / speed));
        } else {
          chmin(dp[bit | (1 << nxt)][nxt],
                dp[bit][cur] + (dis(B[cur - N], A[nxt]) / speed));
        }
      }

      rep(nxt, M) {
        if ((bit >> (nxt + N)) & 1) {
          continue;
        }

        if (cur < N) {
          chmin(dp[bit | (1 << (nxt + N))][nxt + N],
                dp[bit][cur] + (dis(A[cur], B[nxt]) / speed));
        } else {
          chmin(dp[bit | (1 << (nxt + N))][nxt + N],
                dp[bit][cur] + (dis(B[cur - N], B[nxt]) / speed));
        }
      }
    }
  }

  double ans = 1e17;

  rep(i, N) {
    rep(bit, 1 << M) {
      ll nb = ((1 << (N)) - 1) | (bit << N);
      chmin(ans, dp[nb][i] +
                     (dis(mp(0., 0.), A[i]) / pow(2, __builtin_popcount(bit))));
    }
  }

  cout << fixed << setprecision(10) << ans << "\n";
}

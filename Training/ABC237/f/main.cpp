#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll dp[1010][12][12][12]{0LL};

int main() {
  ll N, M, mod = 998244353;
  cin >> N >> M;

  dp[0][11][11][11] = 1;

  rep(i, N) {
    rep(a, 12) {
      rep(b, 12) {
        rep(c, 12) {
          REP(k, 1, M + 1) {
            if (c >= k) {
              ll na = min(a, k), nb = b, nc = c;

              if (a < k)
                chmin(nb, (ll)k);
              if (b < k)
                chmin(nc, (ll)k);

              dp[i + 1][na][nb][nc] += dp[i][a][b][c];
              dp[i + 1][na][nb][nc] %= mod;
            }
          }
        }
      }
    }
  }

  ll ans = 0;

  rep(a, 12) {
    rep(b, 12) {
      rep(c, 11) {
        ans += dp[N][a][b][c];
        ans %= mod;
      }
    }
  }

  cout << ans << "\n";
}

/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

ll dp[1771561]{0}, T[1771561]{0};

int main() {
  ll N;
  in(N);

  rep(_, N) {
    string S;
    ll V;
    in(S, V);

    ll cur = 0;
    rep(i, 6) cur *= 11, cur += int(S[i] - '0') + 1;

    dp[cur] += V;
  }

  vi pt(7);
  pt[0] = 1;
  rep(i, 6) pt[i + 1] = pt[i] * 11;

  rep(k, 6) {
    rep(i, 1771561) {
      if ((i / pt[k]) % 11 < 10) {
        dp[i + pt[k]] += dp[i];
      }
    }
  }

  ll Q;
  in(Q);

  while (Q--) {
    string x, y;
    in(x, y);

    bool flag = false;

    vi X, Y;

    rep(i, 6) {
      X.emplace_back(x[i] - '0'), Y.emplace_back(y[i] - '0' + 1);
      if (X[i] >= Y[i]) {
      }
    }

    if (flag) {
      out(0);
      continue;
    }

    ll res = 0;

    rep(bit, 1 << 6) {
      ll cur = 0;

      rep(i, 6) {
        cur *= 11;
        if ((bit >> i) & 1)
          cur += X[i];
        else
          cur += Y[i];
      }

      res += ll(popcount(uint32_t(bit)) & 1 ? -1 : 1) * dp[cur];
    }

    out(res);
  }
}

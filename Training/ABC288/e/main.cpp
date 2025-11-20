#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return min(a, b); }
ll e() { return 1e18; }

int main() {
  ll N, M;
  cin >> N >> M;
  vi A(N), C(N);
  si X;
  input(A);
  input(C);

  rep(_, M) {
    ll x;
    cin >> x;
    x--;
    X.emplace(x);
  }

  vpii L(N);

  rep(i, N) {
    L[i].first = A[i];
    L[i].second = X.count(i) == 1;
  }

  segtree<ll, op, e> seg(C);

  vvi dp(N + 1, vi(N + 1, 1e18));
  dp[0][0] = 0;

  rep(i, N) {
    ll p, t;
    tie(p, t) = L[i];

    rep(k, i + 1) {
      chmin(dp[i + 1][k + 1], dp[i][k] + p + seg.prod(i - k, i + 1));

      if (t == 0)
        chmin(dp[i + 1][k], dp[i][k]);
    }
  }

  cout << *min_element(all(dp.back())) << "\n";
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll T, M;

  cin >> T >> M;

  vector<vi> D(5005, vi(5005, -1));

  REP(i, 2, 5002) {
    ll cur = 1, k = i;
    while (k >= 2) {
      cur *= k;
      cur %= M;
      D[i][k - 1] = cur;
      k--;
    }
  }

  while (T--) {
    ll N;
    cin >> N;

    vi C(N);
    rep(i, N) cin >> C[i];

    ll cur = C[0], ans = 1;

    REP(i, 1, N) {
      ans *= D[cur + C[i]][C[i]];
      ans %= M;
    }

    cout << ans << endl;
  }
}

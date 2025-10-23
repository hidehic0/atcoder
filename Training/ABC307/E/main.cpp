#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;
  modint998244353 a = 0, b = M, ans = 0;

  rep(i, N - 2) {
    modint998244353 na = b * (M - 1) + a * (M - 2), nb = a;
    a = na;
    b = nb;
  }

  ans += a * (M - 2);
  ans += b * (M - 1);

  cout << ans.val() << "\n";
}

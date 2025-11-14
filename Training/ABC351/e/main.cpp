#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll solve(vi A) {
  sort(all(A));
  ll res = 0;
  ll cur = 0;
  rep(i, A.size()) {
    res += A[i] * i - cur;
    cur += A[i];
  }
  return res;
}

int main() {
  ll N;
  cin >> N;

  vi AX, AY, BX, BY;

  rep(_, N) {
    ll x, y;
    cin >> x >> y;

    ll nx = (x + y), ny = (y - x);

    if ((x + y) % 2) {
      AX.emplace_back(nx);
      AY.emplace_back(ny);
    } else {
      BX.emplace_back(nx);
      BY.emplace_back(ny);
    }
  }

  ll ans = 0;

  ans += solve(AX);
  ans += solve(AY);
  ans += solve(BX);
  ans += solve(BY);

  cout << ans / 2 << "\n";
}

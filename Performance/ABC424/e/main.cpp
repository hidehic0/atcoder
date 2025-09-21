#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll T;
  cin >> T;
  while (T--) {
    ll N, K, X;
    cin >> N >> K >> X;
    map<ld, ll> D;

    rep(_, N) {
      ld a;
      cin >> a;
      D[a]++;
    }

    while (true) {
      auto it = prev(D.end());
      ld k;
      ll c;
      tie(k, c) = *it;

      if (c >= K) {
        D[k / 2] += K * 2;
        D[k] -= K;
        break;
      }

      K -= c;
      D[k / 2] += c * 2;
      D.erase(it);
    }

    ll cur = 0;
    auto it = prev(D.end());

    while (true) {
      auto [k, c] = *it;
      cur += c;
      if (cur >= X) {
        cout << fixed << setprecision(15) << k << endl;
        break;
      }
      it = prev(it);
    }
  }
}

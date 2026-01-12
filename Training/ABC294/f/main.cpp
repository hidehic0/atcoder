#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, K;
  cin >> N >> M >> K;
  VC<pair<ld, ld>> A(N), B(M);
  cin >> A >> B;

  ld left = 0, right = 1;

  rep(_, 100) {
    ld mid = (left + right) / (ld)2;

    ll cnt = 0;
    VC<ld> C;

    for (auto [c, d] : B) {
      // cout << setprecision(100) << ((ld)100 - mid) * c + mid * d << "\n";
      C.emplace_back((c + d) * mid - c);
    }
    sort(all(C));

    for (auto [a, b] : A) {
      cnt += upper_bound(all(C), a - (a + b) * mid) - C.begin();
    }

    if (cnt >= K)
      left = mid;
    else
      right = mid;
  }
  left *= (ld)100;

  cout << setprecision(20) << left << "\n";
}

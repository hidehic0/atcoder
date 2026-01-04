#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll N;
  cin >> N;
  vi L;
  for (ll x = 1; x <= 4000; x++) {
    for (ll y = x + 1; y <= 4000; y++) {
      if (x * x + y * y <= N) {
        L.emplace_back(x * x + y * y);
      }
    }
  }

  sort(all(L));
  vpii T;
  ll prev = -1;

  rep(i, L.size()) {
    if (L[i] == prev)
      T.back().second++;
    else
      T.emplace_back(L[i], 1);
    prev = L[i];
  }
  vi ans;

  for (auto [a, b] : T) {
    if (b == 1)
      ans.emplace_back(a);
  }

  cout << ans.size() << "\n";

  rep(i, ans.size()) { cout << ans[i] << (i + 1 == ans.size() ? "\n" : " "); }
}

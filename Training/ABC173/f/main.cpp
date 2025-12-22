#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;

  ll ans = 0;
  for (ll i = 1; i <= N; i++)
    ans += i * (i + 1) / 2;
  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;

    if (b < a)
      swap(a, b);

    ans -= a * (N - b + 1);
  }

  cout << ans << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  vi H(N);
  cin >> H;

  stack<pii> ST;
  ST.emplace(0, 1);

  ll cur = 0;
  rep(i, N) {
    ll ns = 0;
    while (!ST.empty() && ST.top().first < H[i]) {
      ns += ST.top().second;
      cur += (H[i] - ST.top().first) * ST.top().second;
      ST.pop();
    }

    ST.emplace(H[i], ns);
    ST.emplace(1, 1);
    cur++;

    cout << cur << (i + 1 == N ? "\n" : " ");
  }
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

pii op(pii a, pii b) { return {a.first + b.first, a.second + b.second}; }
pii e() { return {0, 0}; }
pii mapping(ll l, pii r) { return {r.first + r.second * l, r.second}; }
ll composition(ll l, ll r) { return l + r; }
ll id() { return 0; }

int main() {
  ll N;
  cin >> N;
  vi B(N), P(N);
  cin >> B;
  rep(i, N) B[i]--;
  rep(i, N) P[B[i]] = i;

  fenwick_tree<ll> ft(N);
  rep(i, N) ft.add(i, 1);

  ll ans = (N * (N + 1)) / 2;

  rrep(i, N) {
    ft.add(P[i], -1);
    ans += ft.sum(0, P[i]) * ft.sum(P[i], N);
  }

  cout << ans << "\n";
}

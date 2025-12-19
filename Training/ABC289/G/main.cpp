#include <bits/stdc++.h>
using namespace std;

#include "geometry/convexhulltrick.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;
  vi B(N), C(M), SC;
  cin >> B >> C;
  SC = C;
  sort(all(SC));

  vpii F;
  mii D;

  rep(i, N) D[B[i]]++;

  ll cur = N;

  for (auto [c, n] : D) {
    F.emplace_back(cur, c * cur);
    cur -= n;
  }

  sort(all(F));

  ConvexHullTrick<true, ll> CHT;

  for (auto [a, b] : F)
    CHT.add_func(a, b);

  mii res;

  for (ll x : SC)
    res[x] = CHT.query(x);

  rep(i, M) { cout << res[C[i]] << (i + 1 == M ? "\n" : " "); }
}

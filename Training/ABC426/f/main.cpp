#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op1(ll a, ll b) { return a + b; }
ll e1() { return 0; }

ll op2(ll a, ll b) { return min(a, b); }
ll e2() { return LONG_LONG_MAX - 1e18; }
ll mapping(ll a, ll b) { return a + b; }
ll composition(ll a, ll b) { return a + b; }

bool g(ll a) { return a >= 0; }

int main() {
  ll N, Q;
  cin >> N;
  vi A(N);
  input(A);
  cin >> Q;

  segtree<ll, op1, e1> seg1(vi(N, 1));
  lazy_segtree<ll, op2, e2, ll, mapping, composition, e1> seg2(A);

  while (Q--) {
    ll l, r, k;
    input(l, r, k);

    ll res = seg1.prod(l - 1, r) * k;
    seg2.apply(l - 1, r, -k);

    while (seg2.prod(l - 1, r) < 0) {
      ll ind = seg2.max_right<g>(l - 1);

      res += seg2.get(ind);
      seg1.set(ind, 0);
      seg2.set(ind, LONG_LONG_MAX - 1e18);
    }

    cout << res << "\n";
  }
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, Q;
string T;

struct S {
  ll l, r, lll, lr, mx;
  bool p;
};

S op(S a, S b) {
  if (a.l == -1) {
    return b;
  }
  if (b.r == -1)
    return a;
  if (a.l > b.l)
    swap(a, b);

  S res{};

  res.l = a.l;
  res.r = b.r;
  res.mx = max(a.mx, b.mx);
  res.lll = a.lll;
  res.lr = b.lr;
  res.p = false;

  if (T[a.r] == T[b.l]) {
    chmax(res.mx, a.lr + b.lll);

    if (a.p) {
      res.lll += b.lll;
    }
    if (b.p) {
      res.lr += a.lr;
    }

    res.p = a.p & b.p;
  }

  return res;
}

S e() { return S{-1, -1, 0, 0, 0, false}; }

int main() {
  cin >> N >> Q >> T;
  VC<S> v;

  rep(i, N) { v.push_back(S{i, i, 1, 1, 1, true}); }

  segtree<S, op, e> seg(v);

  while (Q--) {
    ll t;
    cin >> t;
    if (t == 1) {
      ll i;
      char x;
      cin >> i >> x;
      i--;
      T[i] = x;
      seg.set(i, S{i, i, 1, 1, 1, true});
    } else {
      ll l, r;
      cin >> l >> r;
      cout << seg.prod(l - 1, r).mx << "\n";
    }
  }
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/fenwicktree.hpp>
#include <atcoder/segtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include "utils/compress.hpp"

ll Q, K;
ll op(ll a, ll b) { return max(a, b); }
ll e() { return -1e18; }

bool g(ll a) { return a <= K; }

int main() {
  cin >> Q >> K;

  vi T(Q), X(Q);
  rep(i, Q) cin >> T[i] >> X[i];

  auto x_map = compress_1d(X);
  ll N = x_map.size();

  fenwick_tree<ll> ft(N);
  segtree<ll, op, e> seg_l(N), seg_r(N);
  si S;

  rep(i, Q) {
    if (T[i] == 1) {
      if (S.count(X[i])) {
        if (*S.begin() != X[i]) {
          auto it = S.lower_bound(X[i]);
          seg_r.set(
              x_map[*prev(it)],
              (it == prev(S.end()) ? LONG_LONG_MAX : *next(it) - *prev(it)));
        }

        if (*prev(S.end()) != X[i]) {
          auto it = S.lower_bound(X[i]);
          seg_l.set(x_map[*next(it)],
                    (it == S.begin() ? LONG_LONG_MAX : *next(it) - *prev(it)));
        }

        seg_l.set(x_map[X[i]], e());
        seg_r.set(x_map[X[i]], e());
        ft.add(x_map[X[i]], -1);
        S.erase(X[i]);
        continue;
      }

      S.emplace(X[i]);
      auto it = S.lower_bound(X[i]);

      if (it != S.begin()) {
        seg_r.set(x_map[*prev(it)], X[i] - *prev(it));
        seg_l.set(x_map[X[i]], X[i] - *prev(it));
      } else {
        seg_l.set(x_map[X[i]], LONG_LONG_MAX);
      }

      if (it != prev(S.end())) {
        seg_l.set(x_map[*next(it)], *next(it) - X[i]);
        seg_r.set(x_map[X[i]], *next(it) - X[i]);
      } else {
        seg_r.set(x_map[X[i]], LONG_LONG_MAX);
      }

      ft.add(x_map[X[i]], 1);
    } else {
      ll res = 1, l, r;
      l = seg_r.min_left<g>(x_map[X[i]]);
      r = seg_l.max_right<g>(x_map[X[i]] + 1);

      if (l != x_map[X[i]])
        res += ft.sum(l, x_map[X[i]]);
      if (r != x_map[X[i]])
        res += ft.sum(x_map[X[i]] + 1, r);

      cout << res << "\n";
    }
  }
}

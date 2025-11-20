#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"
#include "utils/compress.hpp"

pii op(pii a, pii b) { return {a.first + b.first, a.second + b.second}; }
pii e() { return {0, 0}; }

ll X;

bool g(pii a) { return a.second <= X; }

int main() {
  ll N;
  cin >> N;
  vi A(N), B(N), T;
  rep(i, N) cin >> A[i] >> B[i];
  T = A;

  ll Q;
  cin >> Q;
  vector<tuple<ll, ll, ll>> L(Q, {-1, -1, -1});

  rep(i, Q) {
    ll t, x, y = -1;
    cin >> t;

    if (t == 1) {
      cin >> x >> y;
      T.emplace_back(y);
      x--;
    } else if (t == 2) {
      cin >> x >> y;
      x--;
    } else {
      cin >> x;
    }

    t--;
    L[i] = tie(t, x, y);
  }

  auto p_map = compress_1d(T);
  mii p_map_rev;

  for (auto [k, v] : p_map) {
    p_map_rev[v] = k;
  }

  segtree<pii, op, e> seg(N + Q);

  rep(i, N)
      seg.set(p_map[A[i]], op(mp(A[i] * B[i], B[i]), seg.get(p_map[A[i]])));

  rep(ind, Q) {
    ll t, x, y;
    tie(t, x, y) = L[ind];

    if (t == 0) {
      ll a, b;
      tie(a, b) = seg.get(p_map[A[x]]);
      a -= A[x] * B[x];
      b -= B[x];

      seg.set(p_map[A[x]], mp(a, b));

      A[x] = y;
      tie(a, b) = seg.get(p_map[A[x]]);
      a += A[x] * B[x];
      b += B[x];

      seg.set(p_map[A[x]], mp(a, b));
    } else if (t == 1) {
      ll a, b;
      tie(a, b) = seg.get(p_map[A[x]]);
      a -= A[x] * B[x];
      b -= B[x];

      seg.set(p_map[A[x]], mp(a, b));

      B[x] = y;
      tie(a, b) = seg.get(p_map[A[x]]);
      a += A[x] * B[x];
      b += B[x];

      seg.set(p_map[A[x]], mp(a, b));
    } else {
      if (seg.all_prod().second < x) {
        cout << -1 << "\n";
        continue;
      } else if (seg.all_prod().second == x) {
        cout << seg.all_prod().first << "\n";
        continue;
      }

      X = x;
      ll t = seg.min_left<g>(N + Q);

      ll res = seg.prod(t, N + Q).first;

      x -= seg.prod(t, N + Q).second;
      t--;
      res += p_map_rev[t] * x;

      cout << res << "\n";
    }
  }
}

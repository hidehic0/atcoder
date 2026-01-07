#include <bits/stdc++.h>
using namespace std;

#include "data-structure/unionfind.hpp"
#include "grid/template.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll H, W;
  cin >> H >> W;
  vvi F(H, vi(W));
  cin >> F;
  map<ll, vpii> D;

  rep(i, H) rep(k, W) D[-F[i][k]].emplace_back(i, k);

  ll Q;
  cin >> Q;
  vpii L(Q);
  VC<si> A(H * W);

  vi ans(Q);

  rep(i, Q) {
    ll a, b, y, c, d, z;
    cin >> a >> b >> y >> c >> d >> z;
    if (mp(a, b) == mp(c, d))
      ans[i] = abs(y - z);
    else
      A[(a - 1) * W + b - 1].emplace(i), A[(c - 1) * W + d - 1].emplace(i);

    L[i] = mp(y, z);
  }

  UnionFind UF(H * W);

  auto merge = [&](ll a, ll b, ll f) {
    if (UF.same(a, b))
      return;

    a = UF.leader(a), b = UF.leader(b);
    if (UF.data[a] > UF.data[b])
      swap(a, b);

    if (A[a].size() < A[b].size()) {
      swap(A[a], A[b]);
    }

    for (ll ind : A[b]) {
      if (A[a].contains(ind)) {
        if (max(L[ind].first, L[ind].second) <= f) {
          ans[ind] = abs(L[ind].first - L[ind].second);
        } else {
          ans[ind] = abs(L[ind].first - f) + abs(L[ind].second - f);
        }
      } else {
        A[a].emplace(ind);
      }
    }
    A[b].clear();
    UF.merge(a, b);
  };

  for (auto [f, l] : D) {
    for (auto [x, y] : l) {
      for (auto [mx, my] : MOVES1) {
        ll nx = x + mx, ny = y + my;
        if (coordinate_check(nx, ny, H, W) && F[nx][ny] >= F[x][y]) {
          merge(x * W + y, nx * W + ny, -f);
        }
      }
    }
  }

  rep(i, Q) cout << ans[i] << "\n";
}

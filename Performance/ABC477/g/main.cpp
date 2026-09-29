/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

#include "tree/heavy_light_decomposition.hpp"

int main() {
  ll N, Q;
  in(N, Q);
  vi Col(N);
  si CS;
  for (auto &x : Col)
    in(x), --x, CS.emplace(x);

  vvi G(N);

  rep(_, N - 1) {
    ll u, v;
    in(u, v), --u, --v;

    G[u].emplace_back(v), G[v].emplace_back(u);
  }

  HeavyLightDecomposition<ll> hld(G);

  vi V(N * 2, -1), I(N, -1);

  {
    ll ind = 0;

    auto rec = [&](auto rec, ll cur, ll par = -1) -> void {
      I[cur] = ind, V[ind++] = cur;

      for (auto nxt : G[cur]) {
        if (nxt != par) {
          rec(rec, nxt, cur);
        }
      }

      V[ind++] = cur;
    };

    rec(rec, 0);
  }

  ll M = sqrt(N);

  VC<int> B(N / M + 1, 0), A(N + 1, 0), C(N, 0);
  A[0] = CS.size(), B[0] = CS.size();

  VC<int> flip(N, 0);

  VC<int> L(Q), R(Q), X(Q), Y(Q), lca(Q);

  for (auto &&[l, r, x, y] : views::zip(L, R, X, Y))
    in(l, r, x, y), --l, --r;
  rep(i, Q) lca[i] = hld.lca(L[i], R[i]);

  VC<int> ans(Q, 0);

  auto add = [&](ll v) {
    int p = Col[v];
    B[C[p] / M]--, A[C[p]]--;
    C[p]++;
    B[C[p] / M]++, A[C[p]]++;
  };
  auto del = [&](ll v) {
    int p = Col[v];
    B[C[p] / M]--, A[C[p]]--;
    C[p]--;
    B[C[p] / M]++, A[C[p]]++;
  };
  auto save = [&](ll q) {
    rep(i, (X[q] - 1) / M) ans[q] -= B[i];
    rep(i, (X[q] - 1) / M * M, X[q]) ans[q] -= A[i];
    rep(i, Y[q] / M) ans[q] += B[i];
    rep(i, Y[q] / M * M, Y[q] + 1) ans[q] += A[i];

    dump(q, C);
  };
  auto f = [&](ll v) {
    flip[v] ^= 1;
    if (flip[v])
      add(v);
    else
      del(v);
  };

  int bs = (N * 2) / std::min<int>(N * 2, sqrt(Q));

  vpii LR(Q);

  rep(i, Q) LR[i] = minmax(I[L[i]] + 1, I[R[i]] + 1);
  dump(I);

  VC<int> ord(Q);
  ranges::iota(ord, 0);
  ranges::sort(ord, [&](int a, int b) {
    int ablock = LR[a].first / bs, bblock = LR[b].first / bs;
    if (ablock != bblock)
      return ablock < bblock;

    return (ablock & 1) ? LR[a].second > LR[b].second
                        : LR[a].second < LR[b].second;
  });

  int l = 0, r = 0;

  for (auto ind : ord) {
    while (l > LR[ind].first)
      f(V[--l]);
    while (r < LR[ind].second)
      f(V[r++]);
    while (l < LR[ind].first)
      f(V[l++]);
    while (r > LR[ind].second)
      f(V[--r]);

    f(lca[ind]);
    save(ind);
    f(lca[ind]);
  }

  rep(i, Q) out(ans[i]);
}

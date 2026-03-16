/**
 library: https://github.com/hidehic0/library_cpp
**/
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
using namespace atcoder;

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#else
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#endif

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "utils/compress.hpp"

#include <atcoder/lazysegtree>
using namespace atcoder;

pii op(pii a, pii b) {
  if (a.first == b.first)
    return {a.first, a.second + b.second};
  else if (a.first < b.first)
    return a;
  else
    return b;
}
pii e() { return {1e18, 0}; }

pii mapping(ll l, pii r) { return {r.first + l, r.second}; }
ll composition(ll l, ll r) { return l + r; }
ll id() { return 0; }

int main() {
  ll H, W, h, w, N;
  in(H, W, h, w, N);
  if (N == 0) {
    cout << (W - w + 1) * (H - h + 1) << "\n";
    return 0;
  }

  vi R(N), C(N);
  vi LR = {0, H}, LC = {0, W};

  rep(i, N) in(R[i], C[i]);

  LR = R, LC = C;

  rep(i, N) {
    LR.emplace_back(max(0LL, R[i] - h));
    LC.emplace_back(max(0LL, C[i] - w));
  }
  LC.emplace_back(W - w);

  auto xmap = compress_1d(LR), ymap = compress_1d(LC);

  vpii V(ymap.size() - 1);

  auto it = ymap.begin();
  ll ind = 0;
  while (next(it) != ymap.end()) {
    V[ind] = mp(0, next(it)->first - it->first);
    ind++;
    it++;
  }

  lazy_segtree<pii, op, e, ll, mapping, composition, id> seg(V);

  vvpii P(xmap.size()), M(xmap.size() + 1);

  rep(i, N) {
    P[xmap[max(R[i] - h, 0LL)]].emplace_back(ymap[max(C[i] - w, 0LL)],
                                             ymap[C[i]]);
    M[xmap[R[i]]].emplace_back(ymap[max(C[i] - w, 0LL)], ymap[C[i]]);
  }

  ll ans = 0;

  it = xmap.begin();
  ind = 0;
  dump(V, P, M);

  while (it != xmap.end() && it->first <= H - h + 1) {
    if (ind > 0) {
      auto [a, b] = seg.prod(0, ymap[W - w] + 1);
      dump(a, b);
      ans += ((a == 0 ? b : 0)) * (it->first - prev(it)->first);
    }

    for (auto [l, r] : P[ind])
      seg.apply(l, r, 1);
    for (auto [l, r] : M[ind])
      seg.apply(l, r, -1);

    it++;
    ind++;
  }

  out(ans);
}

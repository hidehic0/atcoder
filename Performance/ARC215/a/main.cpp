/**
 library: https://github.com/hidehic0/library_cpp
**/
#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
#include <clocale>
#include <cmath>
#include <functional>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <ostream>
#include <queue>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
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
#include <atcoder/segtree>

ll op(ll a, ll b) { return max(a, b); }
ll e() { return -1e18; }

int main() {
  ll T;
  cin >> T;

  while (T--) {
    ll N, K, L;
    cin >> N >> K >> L;
    vi A(N);
    cin >> A;
    sort(all(A));
    A.erase(unique(all(A)), A.end());
    ll prv = -1;
    segtree<ll, op, e> seg(N);

    rep(i, A.size()) {
      if (prv != -1)
        seg.set(i, A[i] - prv);

      prv = A[i];
    }

    ll l = A[0], r = A.back(), turn = 0, ans = 0;
    vi T = {0};
    vpii D = {{l, L - r}};

    for (; turn < K && seg.all_prod() != e(); turn++) {
      ll mx = seg.all_prod();
      ll ind = seg.max_right(0, [&](ll g) { return g < mx; });
      seg.set(ind, e());

      // if (!(seg.prod(0, ind + 1) == e() || seg.prod(ind, N) == e())) {
      //   ll lind = seg.min_left(ind + 1, [&](ll g) { return g == e(); }) - 1,
      //      rind = seg.max_right(ind, [&](ll g) { return g == e(); });
      //
      //   seg.set(ind, seg.get(lind) + seg.get(rind));
      //   seg.set(lind, e()), seg.set(rind, e());
      // }

      ans += mx / 2, l += mx / 2, r -= mx / 2;
      T.emplace_back(ans);
      D.emplace_back(l, L - r);
    }

    ll res = LONG_LONG_MIN;

    rep(turn, T.size()) {
      auto [tl, tr] = D[turn];
      if (K - turn > 0)
        T[turn] += max(tl, tr);

      chmax(res, T[turn] + max(K - turn - 1, 0LL) * (tl + tr));
    }

    cout << res << "\n";
  }
}

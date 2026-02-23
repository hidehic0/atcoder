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
#include "utils/compress.hpp"
#include <atcoder/segtree>
using namespace atcoder;

struct S {
  ll x, y, z;
};

S op(S a, S b) { return S{max(a.x, b.x), max(a.y, b.y), max(a.z, b.z)}; }
S e() { return S{(ll)-1e18, (ll)-1e18, (ll)-1e18}; }

int main() {
  ll T;
  cin >> T;
  while (T--) {
    ll N;
    cin >> N;
    vi X(N), Y(N), Z(N);
    rep(i, N) cin >> X[i] >> Y[i] >> Z[i];

    auto xmap = compress_1d(X), ymap = compress_1d(Y), zmap = compress_1d(Z);

    segtree<S, op, e> seg1(N), seg2(N), seg3(N);

    rep(i, N) {
      seg1.set(xmap[X[i]], op(seg1.get(xmap[X[i]]), S{X[i], Y[i], Z[i]}));
      seg2.set(ymap[Y[i]], op(seg2.get(ymap[Y[i]]), S{X[i], Y[i], Z[i]}));
      seg3.set(zmap[Z[i]], op(seg3.get(zmap[Z[i]]), S{X[i], Y[i], Z[i]}));
    }

    auto [x, y, z] = seg1.all_prod();
    ll ans = 0;

    rep(i, N) {
      S a = seg1.prod(0, xmap[X[i]] + 1);
      S b = seg2.prod(0, ymap[Y[i]] + 1);
      S c = seg3.prod(0, zmap[Z[i]] + 1);

      if (x == max({a.x, b.x, c.x}) || y == max({a.y, b.y, c.y}) ||
          z == max({a.z, b.z, c.z}))
        ans++;
    }

    cout << ans << "\n";
  }
}

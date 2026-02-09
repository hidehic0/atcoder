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

ll op(ll a, ll b) { return max(a, b); }
ll e() { return -1e18; }

ll op2(ll a, ll b) { return min(a, b); }
ll e2() { return 1e18; }

int main() {
  ll N, D;
  cin >> N >> D;
  vi A(N), L;
  cin >> A;
  L = A;
  rep(i, N) {
    L.emplace_back(A[i] - D + 1);
    L.emplace_back(A[i] + D - 1);
  }

  auto lmap = compress_1d(L);
  vi M(N);
  segtree<ll, op2, e2> seg1(L.size());
  segtree<ll, op2, e2> seg2(N);
  dump(lmap);

  rrep(i, N) {
    ll n = seg1.prod(lmap[A[i] - D + 1], lmap[A[i] + D - 1] + 1);
    dump(i, n);
    if (n != 1e18)
      seg2.set(i, n);
    seg1.set(lmap[A[i]], i);
  }

  ll ans = 0;

  rep(i, N) {
    ll left = i, right = N;
    while (right - left > 1) {
      ll mid = (left + right) / 2;
      dump(i, mid, seg2.prod(i, mid + 1));

      if (seg2.prod(i, mid + 1) > mid)
        left = mid;
      else
        right = mid;
    }

    ans += left - i + 1;
  }

  cout << ans << "\n";
}

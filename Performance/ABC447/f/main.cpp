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
#include "tree/rerooting.hpp"

pii op(pii a, pii b) { return {max(a.first, b.first), a.second + b.second}; }
pii add_root(pii a, ll ind) {
  if (a.second <= 1) {
    return {(ll)-1e18, 1};
  } else if (a.second == 2) {
    return {1, 1};
  } else {
    return {max(a.first, 0LL) + 1, 1};
  }
}

int main() {
  ll Q;
  cin >> Q;

  while (Q--) {
    ll N;
    cin >> N;
    vvi G(N);
    rep(_, N - 1) {
      ll a, b;
      cin >> a >> b;
      a--, b--;
      G[a].emplace_back(b), G[b].emplace_back(a);
    }

    auto res = rerooting(G, op, add_root, {(ll)-1e18, 0});
    ll ans = 0;
    rep(i, N) chmax(ans, res[i].first);

    out(ans);
  }
}

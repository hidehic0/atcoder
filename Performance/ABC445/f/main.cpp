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

int main() {
  ll N, K;
  cin >> N >> K;
  vvi C(N, vi(N));
  cin >> C;

  vvvi dp(31, vvi(N, vi(N, 2e18)));
  dp[0] = C;

  rep(i, 1, 30) {
    rep(u, N) {
      rep(v, N) {
        rep(k, N) { chmin(dp[i][u][k], dp[i - 1][u][v] + dp[i - 1][v][k]); }
      }
    }
  }

  vi ans(N);

  rep(i, N) {
    vi used(N, 2e18);
    used[i] = 0;

    rrep(k, 31) {
      if (!((K >> k) & 1))
        continue;

      vi ndp(N, 2e18);

      rep(u, N) {
        rep(v, N) { chmin(ndp[v], used[u] + dp[k][u][v]); }
      }

      used = ndp;
    }

    cout << used[i] << "\n";
  }
}

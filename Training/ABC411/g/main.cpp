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

#include <atcoder/modint>
using mint = atcoder::modint998244353;
using vm = vector<mint>;
using vvm = vector<vm>;
using vvvm = vector<vvm>;
using pmm = pair<mint, mint>;
ostream &operator<<(ostream &os, const mint &i) {
  os << i.val();
  return os;
}
#ifdef ONLINE_JUDGE
#else
namespace cpp_dump::_detail {
template <int m>
inline std::string
export_var(const atcoder::static_modint<m> &mint, const std::string &indent,
           std::size_t last_line_length, std::size_t current_depth,
           bool fail_on_newline, const export_command &command) {
  return export_var(mint.val(), indent, last_line_length, current_depth,
                    fail_on_newline, command);
}
template <int m>
inline std::string
export_var(const atcoder::dynamic_modint<m> &mint, const std::string &indent,
           std::size_t last_line_length, std::size_t current_depth,
           bool fail_on_newline, const export_command &command) {
  return export_var(mint.val(), indent, last_line_length, current_depth,
                    fail_on_newline, command);
}
} // namespace cpp_dump::_detail
#endif

int main() {
  ll N, M;
  cin >> N >> M;

  vvm G(N, vm(N));

  mint ans = 0;
  rep(_, M) {
    ll a, b;
    cin >> a >> b;
    a--, b--;
    G[a][b]++, G[b][a]++;
  }

  rep(i, N) { rep(k, i + 1, N) ans += G[i][k] * (G[i][k] - 1); }

  rep(n, 2, N) {
    vvm dp(1 << (n + 1), vm(n + 1, 0));
    dp[1 << n][n] = 1;

    rep(bit, dp.size()) {
      rep(cur, n + 1) {
        if (!((bit >> cur) & 1))
          continue;

        if (popcount((unsigned)bit) >= 3) {
          ans += dp[bit][cur] * G[cur][n];
          dump(bit, cur, dp[bit][cur] * G[cur][n]);
        }

        rep(nxt, n + 1) {
          if ((bit >> nxt) & 1)
            continue;

          dp[bit | (1 << nxt)][nxt] += dp[bit][cur] * G[cur][nxt];
        }
      }
    }
    dump(dp);
  }

  ans /= 2;

  cout << ans << "\n";
}

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
#include "utils/factorial.hpp"

#include <atcoder/convolution>
using namespace atcoder;
#include <atcoder/modint>
using mint = atcoder::modint1000000007;
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
  N++;
  ll A = ceil_div(N, 2LL), B = N / 2;
  Fact<mint> Ft(M + A + 1);

  vvm dp(2, vm(M + 1));

  mint cur = 0;

  rrep(i, M + 1) {
    dp[0][i] =
        Ft[M - i + A] * (M - i == 0 ? 1 : Ft.getinv(M - i)) * Ft.getinv(A) -
        cur;
    cur += dp[0][i];
  }

  cur = 0;

  rrep(i, M + 1) {
    dp[1][i] =
        Ft[M - i + B] * (M - i == 0 ? 1 : Ft.getinv(M - i)) * Ft.getinv(B) -
        cur;
    cur += dp[1][i];
  }

  mint ans = 0, a = 0, b = 0;

  rrep(i, M + 1) {
    a += dp[0][i], b += dp[1][i];
    ans += (dp[0][i] * b + dp[1][i] * a - dp[0][i] * dp[1][i]) - ans;
  }

  cout << ans << "\n";
}

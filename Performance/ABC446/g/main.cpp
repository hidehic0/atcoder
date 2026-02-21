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
  ll N;
  cin >> N;
  vi A(N);
  cin >> A;

  VC<deque<ll>> L(N);

  rep(i, N) A[i]--, L[A[i]].emplace_back(i);

  vm D(N, 0), dp(N, 0);
  vi P(N, -1);
  vb used(N, false);
  mint cur = 0, ans = 0, S = 0;

  rep(i, N) {
    if (L[A[i]].size() > A[i]) {
      mint tmp = S - D[A[i]];
      if (P[A[i]] != -1)
        tmp -= dp[P[A[i]]];
      else
        tmp++;

      dp[L[A[i]][A[i]]] += tmp;
    }

    mint tmp = S;
    S -= D[A[i]];
    D[A[i]] = tmp;
    S += dp[i];
    ans += dp[i];
    P[A[i]] = i, L[A[i]].pop_front();
  }

  cout << ans << "\n";
}

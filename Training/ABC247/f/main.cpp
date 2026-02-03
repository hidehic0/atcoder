/**
 library: https://github.com/hidehic0/library_cpp
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define expert_command
#else
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#endif

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

#include "data-structure/unionfind.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  vi P(N), Q(N);
  cin >> P >> Q;

  UnionFind UF(N);

  rep(i, N) UF.merge(P[i] - 1, Q[i] - 1);

  vvvm dp(N + 1, vvm(2, vm(2, 0)));
  dp[0][0][0] = 1;
  dp[0][1][1] = 1;

  rep(i, N) {
    rep(a, 2) {
      dp[i + 1][a][0] += dp[i][a][0] + dp[i][a][1];
      dp[i + 1][a][1] += dp[i][a][0];
    }
  }

  dump(dp);

  mint ans = 1;

  rep(i, N) {
    if (UF.leader(i) != i)
      continue;
    ll sz = UF.size(i) - 2;

    if (sz == -1)
      continue;

    ans *= dp[sz][0][0] * mint{2} + dp[sz][0][1] + dp[sz][1][0] + dp[sz][1][1];
  }

  cout << ans << "\n";
}

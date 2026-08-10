/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

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
  string S;
  in(N, M, S);

  vvi G(N);

  rep(_, M) {
    ll a, b;
    in(a, b), a--, b--;

    G[a].emplace_back(b), G[b].emplace_back(a);
  }

  vb used(N);
  mint ans = 1;
  Fact<mint> F(N * 3);
  bool flag = false;

  rep(i, N) {
    if (used[i])
      continue;

    queue<ll> Q;
    used[i] = true;
    Q.emplace(i);
    vi C(26, 0);

    while (!Q.empty()) {
      ll cur = Q.front();
      Q.pop();

      C[S[cur] - 'a']++;

      for (auto nxt : G[cur]) {
        if (used[nxt])
          continue;

        used[nxt] = true, Q.emplace(nxt);
      }
    }

    ll cnt = 0;
    mint cur = 1;

    rep(i, 26) cnt += C[i], cur *= F.nCr(cnt, C[i]), flag |= C[i] >= 2;

    ans *= cur;
  }

  if (!flag)
    ans /= 2;

  cout << ans << "\n";
}

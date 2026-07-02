/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

using mint = atcoder::modint;
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

void solve() {
  ll N;
  in(N);
  vi A(N), B(N, 0);
  in(A);

  rep(i, N) B[A[i] % N]++;
  mint::set_mod(N);

  rep(i, N) {
    if (B[i] > 1) {
      out(0);
      return;
    }
  }

  mint ans = 1;

  auto rec = [&](const auto &rec, ll l, ll r) -> void {
    if (l == r)
      return;

    ll m = (l + r) >> 1;

    vi F(m - l + 2, 0), G(r - m + 2, 0);

    rep(i, l, m + 1) { F.at(m - i) += B[i]; }
    rep(i, m + 1, r + 1) { G.at(i - m) += B[i]; }

    rec(rec, l, m), rec(rec, m + 1, r);

    auto L = convolution_ll(F, G);

    rep(i, L.size()) ans *= mint{i}.pow(L[i]);
  };

  rec(rec, 0, N - 1);

  cout << ans << "\n";
}

int main() {
  ll T;
  in(T);

  while (T--)
    solve();
}

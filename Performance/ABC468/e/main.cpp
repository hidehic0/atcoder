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
  ll N;
  in(N);

  vi A(N);
  in(A);

  vm B(N + 1);
  rrep(i, 1, N + 1) B[i] = mint{i}.inv() + (i + 1 <= N ? B[i + 1] : 0);

  fenwick_tree<mint> ft1(N + 1), ft2(N + 1);

  rrep(i, 1, N + 1) ft1.add(N - i + 1, mint{i}.inv()),
      ft2.add(N - i + 1, mint{i}.inv() * mint{N - i + 1});

  mint ans = 0;

  rep(i, N) {
    int k = min<ll>(i + 1, N - i);
    ans += mint{k} * A[i];

    dump(k, N - k - 1);

    if (k <= N - k)
      ans += ft1.sum(k, N - k + 1) * A[i] * k;

    ans += ft2.sum(0, k) * A[i];
  }

  cout << ans << "\n";
}

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
  ll N, K;
  in(N, K);

  if (N * 2 <= K) {
    out(0);
    return 0;
  }
  if (N == 1) {
    out(1);
    return 0;
  }

  queue<vm> Q;

  rep(i, 2, N + 1) { Q.push({mint{i}.inv(), mint{i}.inv() * (i - 1)}); }

  while (Q.size() >= 2) {
    auto f = Q.front();
    Q.pop();
    auto g = Q.front();
    Q.pop();
    Q.push(convolution(f, g));
  }

  cout << Q.front()[K - N].val() << "\n";
}

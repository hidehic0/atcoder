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
  int T;
  in(T);

  Fact<mint> F(1e6 + 10);

  while (T--) {
    int N, K;
    in(N, K);

    if ((N < 25) && K > (1LL << N)) {
      out(-1);
      continue;
    }

    vi L;

    rep(i, N + 1) {
      ll n = F.nCr(N, i).val();
      dump(n);

      while (n && L.size() < K) {
        L.emplace_back(i);
        n--;
      }

      if (L.size() == K)
        break;
    }

    ll ans = 0;

    rrep(k, K) {
      int cnt = 0, t = k + 1;
      while (t)
        cnt++, t /= 10;

      ans += L[K - k - 1] * cnt;
    }

    dump(L);

    out(ans);
  }
}

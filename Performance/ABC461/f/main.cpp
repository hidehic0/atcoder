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

vm F(200, 1);
map<tuple<ll, ll, bool>, pmm> D;

pmm rec(ll n, ll s, bool b) {
  dump(n, s);
  if (D.contains({n, s, b})) {
    return D[{n, s, b}];
  }

  if (n == 1) {
    return D[{n, s, b}] = {F[s], F[s]};
  }

  mint t = b ? 0 : (mint{n} * F[s]), p = b ? 0 : F[s];
  ll i = b ? 2 : 1;

  while (i * i <= n) {
    if (n % i != 0) {
      i++;
      continue;
    }

    ll k = n / i;

    auto [x, y] = rec(i, s + 1, i == k);

    t += mint{k} * x + y, p += x;
    i++;
  }

  return (D[{n, s, b}] = {p, t});
}

int main() {
  ll N;
  in(N);

  for (ll i = 2; i <= F.size(); i++) {
    F[i] = F[i - 1] * i;
  }

  cout << rec(N, 1, 0).second << "\n";
}

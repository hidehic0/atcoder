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

Fact<mint> F(4e5);

void solve() {
  ll N, K;
  in(N, K);
  vi A(N);
  in(A);

  if (K == 1) {
    mint ans = 1;
    mii D;
    for (auto a : A)
      D[a]++;

    ll cnt = 0;

    for (auto v : D | views::values) {
      cnt += v;
      ans *= F.nCr(cnt, v);
    }

    cout << ans << "\n";

    return;
  }

  mint ans = 1;
  ll prv = A[0];
  vi T = {A[0]};

  auto mul = [&](const vi &T) -> mint {
    if (T.empty())
      return 1;

    if ((T[0] * 2) % K == 0) {
      mint res = 1;
      mii D;
      for (auto a : T)
        D[a]++;

      ll cnt = 0;
      for (auto v : D | views::values) {
        cnt += v;
        res *= F.nCr(cnt, v);
      }

      return res;
    }

    ll a = 0, b = 0;

    for (auto t : T) {
      if (T[0] % K == t % K)
        a++;
      else
        b++;
    }

    return F.nCr(a + b, b);
  };

  rep(i, 1, N) {
    if (prv % K == A[i] % K || (prv + A[i]) % K == 0) {
    } else {
      ans *= mul(T);
      T.clear();
    }

    T.emplace_back(A[i]);
    prv = A[i];
  }

  ans *= mul(T);

  cout << ans << "\n";
}

int main() {
  ll T;
  in(T);

  while (T--)
    solve();
}

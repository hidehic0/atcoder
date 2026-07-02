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
  ll N, X;
  in(N, X);
  vi A(N), B;
  in(A);

  ll M = (N + 1) / 2;

  rep(i, M) B.emplace_back(A[i]);
  sort(all(B));
  B.erase(unique(all(B)), B.end());

  vvvi L(B.size(), vvi(M + 1));
  VC C(B.size(), vvm(M + 1));
  vm P(N + 1);

  mint cur = 1;

  rep(n, 1, N + 1) {
    cur *= n, cur /= N - n + 1;
    P[n] = cur;
  }
  dump(P);

  mint ans = 0;

  rep(bit, 1, 1 << M) {
    ll ma = -1e18, su = 0, pp = 0;

    rep(i, M) {
      if (!((bit >> i) & 1))
        continue;

      su += A[i], pp++;
      chmax(ma, A[i]);
    }

    if (su >= X && su - ma < X) {
      ans += su * P[pp];
    }

    L[lower_bound(all(B), ma) - B.begin()][pp].emplace_back(su);
  }

  rep(i, B.size()) rep(k, M + 1) {
    sort(all(L[i][k]));
    C[i][k].emplace_back(0);

    rep(t, L[i][k].size()) C[i][k].emplace_back(C[i][k].back() + L[i][k][t]);
  }

  rep(bit, 1, 1 << (N - M)) {
    ll mx = -1e18, su = 0, pp = 0;

    rep(i, N - M) {
      if (!((bit >> i) & 1))
        continue;

      su += A[i + M], pp++;
      chmax(mx, A[i + M]);
    }

    if (su >= X && su - mx < X) {
      dump(su, P[pp]);
      ans += su * P[pp];
    }

    rep(i, B.size()) {
      rep(n, M + 1) {
        ll m = max(B[i], mx);

        ll l = lower_bound(all(L[i][n]), X - su) - L[i][n].begin(),
           r = upper_bound(all(L[i][n]), X - su + m) - L[i][n].begin();

        ans += P[n + pp] * (C[i][n][r] - C[i][n][l]);
      }
    }
  }

  cout << ans << "\n";
}

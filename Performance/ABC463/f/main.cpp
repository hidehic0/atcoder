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
  vi A(2 * N);
  in(A);
  ll M = *ranges::max_element(A);

  vm ans(2 * N);
  bool flag = false;

  {
    // Aの最大値+1がスコアとなった選手が優勝するパターン
    queue<vm> Q;
    vvi C(3);

    rep(i, N) {
      ll a = int(A[2 * i] == M) + int(A[2 * i + 1] == M);
      flag |= a == 2;
      vm f(2);
      f[1] = a;
      f[0] = 2 - a;
      Q.emplace(f);

      if (A[2 * i] == M)
        C[a].emplace_back(2 * i);

      if (A[2 * i + 1] == M)
        C[a].emplace_back(2 * i + 1);
    }

    while (Q.size() > 1) {
      auto f = Q.front();
      Q.pop();
      auto g = Q.front();
      Q.pop();

      Q.emplace(convolution(f, g));
    }

    auto F = Q.front();

    rep(a, 1, 3) {
      ll b = 2 - a;

      mint k = 0, cur = 0;

      rrep(i, 1, F.size()) {
        k += F[i];
        cur += k / a / i;
        k *= -b / a;
      }

      for (auto p : C[a])
        ans[p] += cur;
    }
  }

  if (!flag) {
    // Aの最大値がスコアとなった選手が優勝するパターン
    queue<vm> Q;
    VC C(3, VC(3, VC(3, vi())));

    rep(i, N) {
      ll a = int(A[2 * i] == M) + int(A[2 * i + 1] == M);
      ll b = int(A[2 * i] == M - 1) + int(A[2 * i + 1] == M - 1);
      ll x = 0, y = 0, z = 0;

      if (a == 1) {
        if (b)
          z = 1;
        else
          y = 1;
      } else if (a == 0) {
        x = 2 - b;
        y = b;
      }

      if (A[2 * i] >= M - 1)
        C[x][y][z].emplace_back(2 * i);
      if (A[2 * i + 1] >= M - 1)
        C[x][y][z].emplace_back(2 * i + 1);

      Q.emplace(vm{x, y, z});
    }

    while (Q.size() > 1) {
      auto f = Q.front();
      Q.pop();
      auto g = Q.front();
      Q.pop();

      Q.emplace(convolution(f, g));
    }

    const auto F = Q.front();
    dump(F);

    rep(x, 3) rep(y, 3) rep(z, 3) {
      if (z + y == 0)
        continue;
      if (C[x][y][z].empty())
        continue;

      auto G = F;
      mint cur = 0;

      if (z) {
        rrep(i, 2, F.size()) {
          mint t = G[i] / mint{z};

          cur += t / i;

          G[i] -= t * z;
          G[i - 1] -= t * y;
          G[i - 2] -= t * x;
        }
      } else {
        rrep(i, 1, F.size()) {
          mint t = G[i] / mint{y};

          cur += t / i;

          G[i] -= t * y;
          G[i - 1] -= t * x;
        }
      }

      for (auto p : C[x][y][z]) {
        ans[p] += cur;
      }
    }
  }

  rep(i, 2 * N) cout << ans[i] / mint{2}.pow(N)
                     << (i + 1 == 2 * N ? "\n" : " ");
}

/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll N;
  in(N);
  vi A(N), B(1e6 + 10, -1);
  in(A);

  rep(i, N) B[A[i]] = i;

  dsu UF(N);
  ll ans = 0;

  rrep(i, 1, 1e6 + 10) {
    vi V;

    for (int k = i; k < B.size(); k += i) {
      if (B[k] != -1)
        V.emplace_back(B[k]);
    }

    if (!V.empty())
      dump(V);

    rep(k, V.size() - 1) {
      if (UF.same(V[k], V[k + 1]))
        continue;

      ans += i;
      UF.merge(V[k], V[k + 1]);
    }
  }

  out(ans);
}

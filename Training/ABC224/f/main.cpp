#include <bits/stdc++.h>
using namespace std;
#include <atcoder/lazysegtree>
#include <atcoder/modint>
using namespace atcoder;
using mint = atcoder::modint998244353;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

mint op(mint a, mint b) { return a + b; }
mint e() { return 0; }
mint mapping(mint a, mint b) { return a * b; }
mint composition(mint a, mint b) { return a * b; }
mint id() { return 1; }

int main() {
  string S;
  cin >> S;
  ll N = S.size();

  lazy_segtree<mint, op, e, mint, mapping, composition, id> seg(VC<mint>(N, 0));
  mint ans = 0;

  rrep(i, N) {
    seg.set(i, mint{10}.pow(N - i - 1));
    // rep(i, N) cout << seg.get(i).val() << (i + 1 == N ? "\n" : " ");
    ans += mint{seg.all_prod() * (S[i] - '0')} * mint{2}.pow(i);
    if (i >= N - 1)
      continue;
    seg.apply(i + 1, N, 2);
  }

  cout << ans.val() << "\n";
}

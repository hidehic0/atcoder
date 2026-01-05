#include <bits/stdc++.h>
using namespace std;
#include <atcoder/modint>
using mint = atcoder::modint1000000007;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, K;
  cin >> N >> K;

  VC<mint> cnt(K + 1, 0);

  RREP(k, 1, K + 1) {
    cnt[k] = mint(K / k).pow(N);
    ll i = k * 2;
    while (i <= K) {
      cnt[k] -= cnt[i];
      i += k;
    }
  }

  mint ans = 0;

  REP(i, 1, K + 1) { ans += cnt[i] * i; }
  cout << ans.val() << "\n";
}

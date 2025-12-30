#include <bits/stdc++.h>
using namespace std;
#include <atcoder/convolution>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  vi S(N);
  cin >> S;
  vi A(1e6 + 10);
  rep(i, N) A[S[i]]++;

  auto B = convolution<998244353>(A, A);
  ll ans = 0;

  rep(i, N) { ans += (B[S[i] * 2] - 1) / 2; }

  cout << ans << "\n";
}

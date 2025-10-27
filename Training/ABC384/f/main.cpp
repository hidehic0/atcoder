#include <bits/stdc++.h>
using namespace std;

#include <atcoder/all>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll minas_mod(ll a, ll b) { return (a % b + b) % b; }

int main() {
  ll N;
  cin >> N;
  vi A(N);
  input(A);

  ll ans = 0, prev = 0, acc = 0;

  rrep(k, 26) {
    map<ll, pii> D;
    ll cur = 0;

    rep(i, N) {
      ll cnt, sum;
      tie(cnt, sum) = D[A[i] % (1 << k)];
      cnt += 1;
      sum += A[i];
      D[A[i] % (1 << k)] = {cnt, sum};

      tie(cnt, sum) = D[minas_mod(-A[i], 1 << k)];

      cur += cnt * A[i] + sum;
    }

    ans += (cur - prev) >> k;
    prev = cur;
  }

  cout << ans << "\n";
}

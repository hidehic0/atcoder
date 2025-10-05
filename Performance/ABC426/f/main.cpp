#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

vi D;
vvi L, RS;

int main() {
  ll N, Q;
  cin >> N;
  ll M = sqrtl(N) + 1;
  D.resize(M, 0);
  L.resize(M, {});
  RS.resize(M, {0});

  vi A(N);

  rep(i, N) {
    cin >> A[i];
    L[i / M].emplace_back(A[i]);
  }

  rep(i, M) {
    sort(all(L[i]));
    for (ll a : L[i]) {
      RS[i].emplace_back(RS[i].back() + a);
    }
  }

  cin >> Q;

  while (Q--) {
    ll l, r, k;
    cin >> l >> r >> k;
    l--;
    r--;

    ll ans = 0;

    rep(b, M) {
      if (l <= M * b && (M * (b + 1)) - 1 <= r) {
        ll ind = upper_bound(all(L[b]), max(k - D[b], 0LL)) - L[b].begin();
        ans += RS[b][ind];
        ans += (M - ind) * k;
        D[b] += k;
      } else if (!(M * (b + 1) < l) && !(r < M * b)) {
        L[b].clear();
        REP(i, M * b, M * (b + 1)) {
          if (l <= i && i <= r) {
            ans += min(k, A[i] - D[b]);
            A[i] -= k;
          }

          if (i < N) {
            A[i] -= D[b];
            chmax(A[i], 0LL);
            L[b].emplace_back(A[i]);
          }
        }

        D[b] = 0;
        sort(all(L[b]));
        RS[b] = {0};

        for (ll a : L[b]) {
          RS[b].emplace_back(RS[b].back() + a);
        }
      }
    }

    cout << ans << "\n";
  }
}

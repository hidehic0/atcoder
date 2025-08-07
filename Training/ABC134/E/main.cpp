#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return max(a, b); }

ll e() { return 0; }

int main() {
  ll N;
  cin >> N;
  vi A(N);
  rep(i, N) cin >> A[i];

  segtree<ll, op, e> seg(A);
  si S;
  rep(i, N) S.emplace(i);
  ll ans = 0;

  while (!S.empty()) {
    ans++;
    ll cur = *S.begin();
    S.erase(cur);
    seg.set(cur, -1);

    while (seg.prod(cur + 1, N) > A[cur]) {
      ll left = cur + 1, right = N;

      while (right - left > 1) {
        ll mid = (left + right) / 2;

        if (seg.prod(cur + 1, mid) <= A[cur]) {
          left = mid;
        } else {
          right = mid;
        }
      }

      S.erase(left);
      seg.set(left, -1);
      cur = left;
    }
  }

  cout << ans << endl;
}

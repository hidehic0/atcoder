#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return min(a, b); }
ll e() { return 1e18; }

int main() {
  ll N, M;
  cin >> N >> M;

  VC<deque<ll>> L(M);
  vi A(N);
  cin >> A;
  rep(i, N) {
    A[i]--;
    L[A[i]].emplace_back(i);
  }

  segtree<ll, op, e> seg1(A), seg2(M);

  rep(i, M) { seg2.set(i, L[i].back()); }

  vi res;
  si S;
  ll cur = 0;

  rep(_, M) {
    ll mx = seg2.all_prod();
    ll t = seg1.prod(cur, mx + 1);

    res.emplace_back(t + 1);
    S.emplace(t);

    ll nxt = L[t].front();

    while (cur <= nxt) {
      if (!L[A[cur]].empty()) {

        L[A[cur]].pop_front();
        if (L[A[cur]].size() == 0)
          seg2.set(A[cur], e());
      }

      cur++;
    }

    while (!L[t].empty()) {
      seg1.set(L[t].front(), e());
      L[t].pop_front();
    }

    seg2.set(t, e());
  }

  rep(i, M) cout << res[i] << (i + 1 == M ? "\n" : " ");
}

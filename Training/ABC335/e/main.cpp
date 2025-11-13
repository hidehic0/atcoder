#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;
  vi A(N);
  input(A);
  vvi G(N);

  rep(_, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }

  map<ll, vi> D;

  rep(i, N) { D[A[i]].emplace_back(i); }

  vi ans(N, -1e18);

  auto it = D.begin();

  while (it != D.end()) {
    ll a;
    vi l;
    tie(a, l) = *it;

    si used;

    if (a == A[0]) {
      queue<ll> Q;
      used.emplace(0);
      Q.emplace(0);
      ans[0] = 1;

      while (!Q.empty()) {
        ll cur = Q.front();
        Q.pop();

        for (ll nxt : G[cur]) {
          if (A[nxt] == A[cur] && used.count(nxt) == 0) {
            used.emplace(nxt);
            ans[nxt] = 1;
            Q.emplace(nxt);
          }
        }
      }
      it++;
      continue;
    }

    for (ll i : l) {
      if (used.count(i) == 1)
        continue;

      ll mx = ans[i];

      queue<ll> Q;
      Q.emplace(i);
      used.emplace(i);
      vi t = {i};

      while (!Q.empty()) {
        ll cur = Q.front();
        Q.pop();

        for (ll nxt : G[cur]) {
          if (A[nxt] < A[cur]) {
            chmax(mx, ans[nxt] + 1);
          } else if (A[nxt] == A[cur]) {
            if (used.count(nxt) == 0) {
              used.emplace(nxt);
              Q.emplace(nxt);
              t.emplace_back(nxt);
            }
          }
        }
      }

      for (ll k : t) {
        ans[k] = mx;
      }

      // if (!t.empty()) {
      //   cout << "";
      // }
    }

    it++;
  }

  cout << max(ans.back(), 0LL) << "\n";
}

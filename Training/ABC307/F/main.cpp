#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, K, D;
  cin >> N >> M;
  vvpii G(N);

  rep(_, M) {
    ll u, v, w;
    input(u, v, w);
    u--;
    v--;

    G[u].emplace_back(v, w);
    G[v].emplace_back(u, w);
  }

  cin >> K;
  vi ans(N, -1);
  priority_queue<pii, vector<pii>, greater<pii>> L;

  rep(_, K) {
    ll a;
    cin >> a;
    a--;
    ans[a] = 0;

    for (auto [b, w] : G[a]) {
      if (ans[b] == -1) {
        L.emplace(w, b);
      }
    }
  }

  cin >> D;

  rep(d, D) {
    ll x;
    cin >> x;

    priority_queue<pii, vector<pii>, greater<pii>> PQ;

    while (!L.empty() && L.top().first <= x) {
      auto [cos, cur] = L.top();
      L.pop();
      if (ans[cur] != -1)
        continue;
      PQ.emplace(cos, cur);
    }

    while (!PQ.empty()) {
      auto [cos, cur] = PQ.top();
      PQ.pop();

      if (ans[cur] == -1) {
        ans[cur] = d + 1;
      } else {
        continue;
      }

      for (auto [nxt, w] : G[cur]) {
        if (ans[nxt] == -1) {
          if (cos + w <= x) {
            PQ.emplace(cos + w, nxt);
          } else {
            L.emplace(w, nxt);
          }
        }
      }
    }
  }

  rep(i, N) cout << ans[i] << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using T = tuple<ll, ll, ll>;

int main() {
  ll N, M, K, L;
  cin >> N >> M >> K >> L;
  vi A(N), B(L);
  cin >> A >> B;

  apply_vec<ll>(A, [](ll a) -> ll { return a - 1; });
  apply_vec<ll>(B, [](ll a) -> ll { return a - 1; });

  vvpii G(N);

  rep(_, M) {
    ll u, v, c;
    cin >> u >> v >> c;
    u--;
    v--;

    G[u].emplace_back(v, c);
    G[v].emplace_back(u, c);
  }

  VC<mii> used;

  rep(i, N) used.emplace_back(mii{});

  priority_queue<T, VC<T>, greater<T>> PQ;

  rep(i, L) {
    used[B[i]].emplace(A[B[i]], 0);
    PQ.emplace(0, B[i], A[B[i]]);
  }

  while (!PQ.empty()) {
    auto [cos, cur, cut] = PQ.top();
    PQ.pop();

    if (!used[cur].contains(cut) || used[cur][cut] < cos)
      continue;

    for (auto [nxt, w] : G[cur]) {
      if (used[nxt].contains(cut)) {
        if (used[nxt][cut] <= cos + w)
          continue;
        used[nxt].erase(used[nxt].find(cut));
      } else if (used[nxt].size() == 2) {
        auto it = used[nxt].begin();

        if (it->second < next(it)->second)
          it++;

        if (it->second <= cos + w)
          continue;
        used[nxt].erase(it);
      }

      used[nxt].emplace(cut, cos + w);
      PQ.emplace(cos + w, nxt, cut);
    }
  }

  rep(i, N) {
    ll res = 2e18;
    for (auto [k, v] : used[i]) {
      if (k != A[i]) {
        chmin(res, v);
      }
    }
    cout << (res == 2e18 ? -1 : res) << (i + 1 == N ? "\n" : " ");
  }
}

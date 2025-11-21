#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using T = tuple<ll, ll, ll>;

int main() {
  ll N, M, S;
  cin >> N >> M >> S;

  vi A(M), B(M), C(N), D(N);
  vvpii G(N);

  rep(i, M) {
    ll u, v;
    cin >> u >> v >> A[i] >> B[i];
    u--;
    v--;

    G[u].emplace_back(v, i);
    G[v].emplace_back(u, i);
  }

  rep(i, N) cin >> C[i] >> D[i];

  S = min(S, 5999LL);

  vvi used(N, vi(6000, 1e18));
  used[0][S] = 0;

  priority_queue<T, VC<T>, greater<T>> PQ;
  PQ.emplace(0, 0, S);

  while (!PQ.empty()) {
    ll cos, cur, s;
    tie(cos, cur, s) = PQ.top();
    PQ.pop();

    if (used[cur][s] < cos)
      continue;

    // 両替
    ll ns = min(s + C[cur], 5999LL);
    if (chmin(used[cur][ns], used[cur][s] + D[cur])) {
      PQ.emplace(used[cur][ns], cur, ns);
    }

    // 移動
    for (auto [nxt, ind] : G[cur]) {
      if (s < A[ind])
        continue;
      ll ns = s - A[ind];

      if (chmin(used[nxt][ns], used[cur][s] + B[ind])) {
        PQ.emplace(used[nxt][ns], nxt, ns);
      }
    }
  }

  REP(i, 1, N) { cout << *ranges::min_element(used[i]) << "\n"; }
}

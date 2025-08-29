#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, INF = pow(10, 15);
  cin >> N >> M;

  vi used(N + M, INF);
  vector G(N + M, vi());
  queue<ll> Q;

  rep(i, N) {
    ll a;
    cin >> a;

    rep(_, a) {
      ll s;
      cin >> s;

      s--;
      G[i].emplace_back(s + N);
      G[s + N].emplace_back(i);

      if (s == 0) {
        used[i] = 0;
        Q.push(i);
      }
    }
  }

  while (!Q.empty()) {
    ll cur = Q.front();
    Q.pop();

    for (auto nxt : G[cur]) {
      if (used[nxt] > used[cur] + 1) {
        used[nxt] = used[cur] + 1;
        Q.push(nxt);
      }
    }
  }

  cout << (used[N + M - 1] == INF ? -1 : used[N + M - 1] / 2) << "\n";
}

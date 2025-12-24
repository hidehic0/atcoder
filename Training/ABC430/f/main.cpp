#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll T;
  cin >> T;

  while (T--) {
    ll N;
    string S;
    cin >> N >> S;

    vi C(N + 1), deg(N, 0), order, D(N);
    vvi G(N), RG(N);

    rep(i, N - 1) {
      if (S[i] == 'L') {
        G[i].emplace_back(i + 1);
        RG[i + 1].emplace_back(i);

        deg[i + 1]++;
      } else {
        G[i + 1].emplace_back(i);
        RG[i].emplace_back(i + 1);

        deg[i]++;
      }
    }

    queue<ll> Q;
    rep(i, N) {
      if (deg[i] == 0)
        Q.emplace(i);
    }

    while (!Q.empty()) {
      ll cur = Q.front();
      Q.pop();
      order.emplace_back(cur);
      D[cur] = order.size() - 1;

      for (ll nxt : G[cur]) {
        deg[nxt]--;
        if (deg[nxt] == 0) {
          Q.emplace(nxt);
        }
      }
    }

    vi up(N), down(N);

    rep(i, N) {
      for (ll nxt : G[order[i]]) {
        up[nxt] += up[order[i]] + 1;
      }
    }

    rrep(i, N) {
      for (ll nxt : RG[order[i]]) {
        down[nxt] += down[order[i]] + 1;
      }
    }

    rep(i, N) {
      C[down[i]]++;
      C[N - up[i]]--;
    }
    rep(i, N) {
      C[i + 1] += C[i];
      cout << C[i] << (i + 1 == N ? "\n" : " ");
    }
  }
}

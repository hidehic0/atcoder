#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using bs = bitset<60>;

int main() {
  ll N, M;
  cin >> N;
  vvi G(N);
  vvi T(N, vi(N, -1));

  rep(i, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;

    G[a].emplace_back(b);
    G[b].emplace_back(a);

    T[a][b] = i;
    T[b][a] = i;
  }

  auto getpath = [&](ll a, ll b) {
    queue<ll> Q;
    Q.emplace(a);

    vi prev(N, -1);
    prev[a] = -2;
    bs res{};

    while (!Q.empty()) {
      ll cur = Q.front();
      Q.pop();

      for (ll nxt : G[cur]) {
        if (prev[nxt] == -1) {
          prev[nxt] = cur;
          Q.emplace(nxt);

          if (nxt == b) {
            break;
          }
        }
      }
    }

    ll cur = b;

    while (prev[cur] != -2) {
      res[T[cur][prev[cur]]] = 1;
      cur = prev[cur];
    }

    return res;
  };

  cin >> M;
  VC<bs> P(M);

  bs cur{};

  rep(i, M) {
    ll u, v;
    cin >> u >> v;
    u--;
    v--;
    P[i] = getpath(u, v);

    cur |= P[i];
  }

  ll ans = 0;

  REP(bit, 0, 1 << M) {
    bs tmp;
    ll cnt = 0;

    rep(i, M) {
      if (bit & (1 << i)) {
        tmp |= P[i];
        cnt++;
      }
    }

    if (cnt % 2 == 0) {
      ans += (1LL << ((N - 1) - tmp.count()));
    } else {
      ans -= (1LL << ((N - 1) - tmp.count()));
    }
  }

  cout << ans << "\n";
}

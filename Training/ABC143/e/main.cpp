#include <bits/stdc++.h>
using namespace std;

#include "graph/warshall-floyd.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, L;
  cin >> N >> M >> L;
  vvi D1(N, vi(N, 1e18)), D2(N, vi(N, 1e18));
  rep(i, N) {
    D1[i][i] = 0;
    D2[i][i] = 0;
  }

  rep(_, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;

    if (c > L)
      continue;

    D1[a][b] = c;
    D1[b][a] = c;
  }

  warshall_floyd(D1);

  rep(u, N) {
    rep(v, N) {
      if (D1[u][v] <= L) {
        chmin(D2[u][v], 1LL);
      }
    }
  }

  warshall_floyd(D2);
  ll Q;
  cin >> Q;

  while (Q--) {
    ll s, t;
    cin >> s >> t;
    s--;
    t--;
    cout << (D2[s][t] == 1e18 ? -1 : D2[s][t] - 1) << "\n";
  }
}

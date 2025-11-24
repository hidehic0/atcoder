#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, S, T;
  cin >> N >> M;
  vvi G(N);

  rep(_, M) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;

    G[a].emplace_back(b);
  }

  cin >> S >> T;
  S--;
  T--;

  vvi used(N, vi(3, -1)), prev(N, vi(3, -1));
  used[S][0] = 0;

  deque<pii> Q;
  Q.emplace_front(S, 0);

  while (!Q.empty()) {
    auto [cur, cnt] = Q.front();
    Q.pop_front();

    for (ll nxt : G[cur]) {
      if (cnt == 0) {
        if (used[nxt][2] == -1) {
          used[nxt][2] = used[cur][0] + 1;
          prev[nxt][2] = cur;
          Q.emplace_back(nxt, 2);
        }
      } else {
        if (used[nxt][cnt - 1] == -1) {
          used[nxt][cnt - 1] = used[cur][cnt];
          prev[nxt][cnt - 1] = cur;
          Q.emplace_front(nxt, cnt - 1);
        }
      }
    }
  }

  cout << used[T][0] << "\n";
}

#include <bits/stdc++.h>
using namespace std;

#include "grid/template.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll H, W, K;
  cin >> H >> W >> K;
  spii S;

  vvvi used(H, vvi(W, vi(2, -1)));

  queue<pii> Q;

  rep(_, K) {
    ll r, c;
    cin >> r >> c;
    r--;
    c--;
    Q.emplace(r, c);
    used[r][c][0] = 0;
    used[r][c][1] = 0;
    S.emplace(r, c);
  }

  while (!Q.empty()) {
    ll x, y;
    tie(x, y) = Q.front();
    Q.pop();

    for (auto [mx, my] : MOVES1) {
      ll nx = x + mx, ny = y + my;

      if (!coordinate_check(nx, ny, H, W))
        continue;

      if (used[nx][ny][0] == -1) {
        used[nx][ny][0] = used[x][y][1] + 1;
      } else if (used[nx][ny][1] == -1) {
        used[nx][ny][1] = used[x][y][1] + 1;
        Q.emplace(nx, ny);
      }
    }
  }

  ll ans = 0;

  rep(x, H) {
    rep(y, W) {
      if (used[x][y][1] != -1)
        ans += used[x][y][1];
    }
  }

  cout << ans << "\n";
}

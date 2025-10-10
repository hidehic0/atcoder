#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, H, W;
vector<pii> L;
vvi used;
si A;
map<pair<si, vvi>, bool> T;

bool dfs() {
  if (T.count(mp(A, used)) == 1) {
    return T[mp(A, used)];
  }

  bool flag = true;
  rep(i, H) { rep(k, W) flag &= used[i][k]; }

  if (flag) {
    T[mp(A, used)] = true;
    return true;
  }
  if (A.size() == N) {
    T[mp(A, used)] = false;
    return false;
  }

  rep(x, H) {
    flag = false;
    rep(y, W) {
      if (used[x][y]) {
        continue;
      }

      rep(i, N) {
        if (A.count(i) == 1) {
          continue;
        }

        auto [a, b] = L[i];
        if (x + a <= H && y + b <= W) {
          bool flag = false;

          REP(nx, x, a + x) {
            REP(ny, y, b + y) { flag |= used[nx][ny]; }
          }

          if (!flag) {
            REP(nx, x, a + x) { REP(ny, y, b + y) used[nx][ny] = true; }
            A.emplace(i);
            bool res = dfs();
            A.erase(i);
            REP(nx, x, a + x) { REP(ny, y, b + y) used[nx][ny] = false; }

            if (res) {
              return true;
            }
          }
        }

        swap(a, b);

        if (x + a <= H && y + b <= W) {
          bool flag = false;

          REP(nx, x, a + x) {
            REP(ny, y, b + y) { flag |= used[nx][ny]; }
          }

          if (!flag) {
            REP(nx, x, a + x) { REP(ny, y, b + y) used[nx][ny] = true; }
            A.emplace(i);
            bool res = dfs();
            A.erase(i);
            REP(nx, x, a + x) { REP(ny, y, b + y) used[nx][ny] = false; }

            if (res) {
              T[mp(A, used)] = true;
              return true;
            }
          }
        }

        swap(a, b);
      }

      flag = true;
      break;
    }

    if (flag)
      break;
  }

  T[mp(A, used)] = false;
  return false;
}

int main() {
  cin >> N >> H >> W;
  L.resize(N);
  used.resize(H);

  rep(i, H) used[i].resize(W);
  rep(i, N) cin >> L[i].first >> L[i].second;

  cout << (dfs() ? "Yes" : "No") << "\n";
}

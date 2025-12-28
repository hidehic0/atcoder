#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N;
vvi G;
vi root, sz;

ll dfs(ll cur, ll par = -1) {
  root[cur] = par;
  ll res = 0;
  for (ll nxt : G[cur]) {
    if (nxt != par)
      res += dfs(nxt, cur);
  }

  return sz[cur] = res + 1;
}

int main() {
  cin >> N;
  G.resize(N);
  root.resize(N);
  sz.resize(N);
  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  dfs(0);

  ll ans = 1, A = 0, B = 0, R = N;
  si S = {0};
  ll t = 1;
  for (ll nxt : G[0]) {
    t += sz[nxt];
  }
  for (ll nxt : G[0]) {
    t -= sz[nxt];
    ans += sz[nxt] * t;
  }

  REP(i, 1, N) {
    ll cur = i, d = 0;
    if (S.contains(cur)) {
      if (B == 0) {
        ans += R * sz[A];
      } else {
        ans += sz[A] * sz[B];
      }
      continue;
    }
    while (true) {
      if (cur != 0) {
        d += sz[cur] - d;
      }

      if (cur == A) {
        break;
      } else if (cur == B) {
        swap(A, B);
        break;
      } else if (S.contains(cur)) {
        goto OUTPUT;
      }

      S.emplace(cur);
      cur = root[cur];
    }
    if (A == 0 && B == 0) {

      R -= d;
    }

    A = i;
    if (B == 0) {
      ans += R * sz[A];
    } else {
      ans += sz[A] * sz[B];
    }
  }

OUTPUT:
  cout << ans << "\n";
}

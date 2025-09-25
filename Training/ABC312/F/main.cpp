#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, ans = 0;
vi c_size;
vvi G;

ll dfs(ll cur, ll par = -1) {
  for (auto nxt : G[cur]) {
    if (nxt != par)
      c_size[cur] += dfs(nxt, cur);
  }

  return c_size[cur];
}

void f(ll cur, ll sz, ll par = -1) {
  vi dp(4, 0);
  dp[0] = 1;
  dp[1] = sz;

  for (auto nxt : G[cur]) {
    if (nxt == par) {
      continue;
    }

    rrep(i, 3) { dp[i + 1] += dp[i] * c_size[nxt]; }
  }

  for (auto nxt : G[cur]) {
    if (nxt == par)
      continue;

    f(nxt, sz + c_size[cur] - c_size[nxt], cur);
  }

  ans += dp[3];
}

int main() {
  cin >> N;
  G.resize(N);
  c_size.resize(N, 1);

  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  dfs(0);
  f(0, 0);

  cout << ans << "\n";
}

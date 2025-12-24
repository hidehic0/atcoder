#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N;
vvpii G;

pii dfs(ll cur, ll par = -1) {
  pii res = mp(0, cur);
  for (auto [nxt, w] : G[cur]) {
    if (nxt == par)
      continue;
    pii c = dfs(nxt, cur);
    chmax(res, mp(c.first + w, c.second));
  }

  return res;
}

int main() {
  cin >> N;
  G.resize(N);

  ll ans = 0;

  rep(_, N - 1) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;
    G[a].emplace_back(b, c);
    G[b].emplace_back(a, c);
    ans += c * 2;
  }

  ans -= dfs(dfs(0).second).first;

  cout << ans << "\n";
}

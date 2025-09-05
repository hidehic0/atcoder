#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  vector<vector<pair<ll, ll>>> G(N);
  vector<tuple<ll, ll, ll>> E;

  rep(_, N - 1) {
    ll a, b, w;
    cin >> a >> b >> w;
    a--;
    b--;

    G[a].emplace_back(b, w);
    G[b].emplace_back(a, w);
    E.emplace_back(tie(a, b, w));
  }

  function<pair<ll, ll>(ll, ll, ll)> dfs1 = [&](ll cur, ll b, ll par = -1) {
    pair<ll, ll> l = {1, 0};

    for (auto [nxt, w] : G[cur]) {
      if (nxt == par)
        continue;

      pair<ll, ll> nl = dfs1(nxt, b, cur);

      if (w & (1LL << b)) {
        swap(nl.first, nl.second);
      }

      l.first += nl.first;
      l.second += nl.second;
    }

    return l;
  };

  modint1000000007 ans = 0;

  rep(b, 62) {

    auto [v0, v1] = dfs1(0, b, -1);

    ans += modint1000000007{2}.pow(b) * v1 * v0;
  }

  cout << ans.val() << "\n";
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, INF = 1e16;
vvi G;
vi ans;
vector<pii> memo;

pii max_pair(pii a, pii b) { return max(a, b); }

pii dfs1(ll cur, ll par) {
  pii res = {0, cur};

  rep(ind, G[cur].size()) {
    auto nxt = G[cur][ind];
    if (nxt != par) {
      res = max_pair(res, dfs1(nxt, cur));
    }
  }

  res.first += 1;

  return memo[cur] = res;
}

pii add(pii p) { return {p.first + 1, p.second}; }

void dfs2(ll cur, ll par, pii p) {
  pii tmp = memo[cur];
  tmp.first--;
  ans[cur] = max(p, tmp).second + 1;

  p = max_pair(p, (pii)mp(0, cur));

  set<pii> l = {p};

  rep(ind, G[cur].size()) {
    auto nxt = G[cur][ind];
    if (nxt == par)
      continue;
    l.emplace(memo[nxt]);
  }

  rep(ind, G[cur].size()) {
    auto nxt = G[cur][ind];
    if (nxt == par)
      continue;
    l.erase(memo[nxt]);
    dfs2(nxt, cur, add(*prev(l.end())));
    l.emplace(memo[nxt]);
  }
}

int main() {
  cin >> N;
  G.resize(N);
  ans.resize(N);
  memo.resize(N);

  rep(_, N - 1) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;

    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  dfs1(0, -1);
  dfs2(0, -1, {-INF, -INF});

  rep(i, N) { cout << ans[i] << "\n"; }
}

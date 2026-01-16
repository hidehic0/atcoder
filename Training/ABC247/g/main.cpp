#include <bits/stdc++.h>
using namespace std;
#include <atcoder/mincostflow>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using T = tuple<ll, ll, ll>;

int main() {
  ll N, INF = 1e11;
  cin >> N;

  VC<T> E;

  rep(_, N) {
    ll a, b, c;
    cin >> a >> b >> c;
    E.emplace_back(a - 1, b - 1, c);
  }

  vi ans;

  REP(i, 1, 151) {
    mcf_graph<ll, ll> G(300 + 2);
    ll sink = 300 + 1;

    for (auto [a, b, c] : E)
      G.add_edge(a, b + 150, 1, INF - c);

    rep(i, 150) G.add_edge(sink - 1, i, 1, 0), G.add_edge(i + 150, sink, 1, 0);

    auto t = G.flow(sink - 1, sink, i);

    if (t.first != i)
      break;

    ans.emplace_back(t.second);
  }

  cout << ans.size() << "\n";

  rep(i, ans.size()) cout << -(ans[i] - INF * (i + 1)) << "\n";
}

#include <bits/stdc++.h>
using namespace std;
#include <atcoder/maxflow>
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll H, W, N;
  cin >> H >> W >> N;
  mf_graph<ll> G(N * 2 + H + W + 2);
  ll sink = H + N * 2 + W + 1, fx = N * 2, fy = N * 2 + H;

  rep(i, N) {
    ll a, b, c, d;
    cin >> a >> b >> c >> d;
    G.add_edge(i, i + N, 1);

    REP(x, a - 1, c) {
      G.add_edge(fx + x, i, 1);
      REP(y, b - 1, d) { G.add_edge(i + N, fy + y, 1); }
    }
  }

  rep(x, H) G.add_edge(sink - 1, fx + x, 1);
  rep(y, W) G.add_edge(fy + y, sink, 1);

  cout << G.flow(sink - 1, sink) << "\n";
}

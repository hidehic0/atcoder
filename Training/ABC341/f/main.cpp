#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;

  vvi G(N);

  rep(_, M) {
    ll a, b;
    cin >> a >> b;
    a--;
    b--;
    G[a].emplace_back(b);
    G[b].emplace_back(a);
  }

  vi W(N), A(N), P(N);
  input(W);
  input(A);

  iota(all(P), 0);
  sort(all(P), [&](ll a, ll b) { return W[a] < W[b]; });
  ll ans = 0;
  vi memo(N, 0);

  for (ll u : P) {
    vi dp(W[u], -1e17);
    dp[0] = 0;

    for (ll v : G[u]) {
      rrep(i, W[u]) {
        if (i + W[v] < W[u]) {
          chmax(dp[i + W[v]], dp[i] + memo[v]);
        }
      }
    }

    ll t = *max_element(all(dp));

    memo[u] = t + 1;
    ans += (t + 1LL) * A[u];
  }

  out(ans);
}

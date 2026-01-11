#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, K, X, cnt;
vi A, ans;

bool dfs(ll i, ll k, ll t) {
  if (i == N) {
    if (k == 0) {
      ans.emplace_back(t);
      return ans.size() == X;
    }

    return false;
  }

  rrep(p, k + 1) {
    bool b = dfs(i + 1, k - p, t + A[i] * p);
    if (b)
      return true;
  }
  return false;
}

using T = tuple<ll, ll, ll>;

int main() {
  cin >> N >> K >> X;
  A.resize(N);
  cin >> A;
  sort(all(A), greater<ll>{});
  A.emplace_back(0);

  priority_queue<T> PQ;
  PQ.emplace(-K, 0, 0);

  while (!PQ.empty() && ans.size() < X) {
    auto [k, t, i] = PQ.top();
    k *= -1;
    PQ.pop();

    if (i == N) {
      if (k == 0)
        ans.emplace_back(t);
      continue;
    }

    rrep(p, k + 1) { PQ.emplace(-(k - p), t + A[i] * p, i + 1); }
  }
  sort(all(ans), greater<ll>{});

  rep(i, X) cout << ans[i] << "\n";
}

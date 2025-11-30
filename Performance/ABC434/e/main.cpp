#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;
  map<ll, si> D;
  vpii L(N);

  rep(i, N) {
    ll x, r;
    cin >> x >> r;
    L[i] = mp(x - r, x + r);
    D[x - r].emplace(i);
    D[x + r].emplace(i);
  }

  si S;

  deque<ll> Q;
  vb used(N);

  rep(i, N) {
    auto [a, b] = L[i];
    if (D[a].size() == 1) {
      Q.emplace_front(i);
    } else if (D[b].size() == 1) {
      Q.emplace_front(i);
    } else {
      Q.emplace_back(i);
    }
  }

  while (!Q.empty()) {
    ll ind = Q.front();
    Q.pop_front();
    if (used[ind])
      continue;

    used[ind] = true;

    auto [a, b] = L[ind];

    if (D[a].size() == 1 && !S.contains(a)) {
      S.emplace(a);
      D[a].erase(ind);
      D[b].erase(ind);

      if (D[b].size() == 1) {
        Q.emplace_front(*D[b].begin());
      }
    } else if (D[b].size() == 1 && !S.contains(a)) {
      S.emplace(b);
      D[a].erase(ind);
      D[b].erase(ind);

      if (D[a].size() == 1) {
        Q.emplace_front(*D[a].begin());
      }
    } else if (!S.contains(a)) {
      S.emplace(a);
      D[a].erase(ind);
      D[b].erase(ind);

      if (D[b].size() == 1) {
        Q.emplace_front(*D[b].begin());
      }
    } else if (!S.contains(b)) {
      S.emplace(b);
      D[a].erase(ind);
      D[b].erase(ind);

      if (D[a].size() == 1) {
        Q.emplace_front(*D[a].begin());
      }
    }
  }

  cout << S.size() << "\n";
}

#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;

  map<ll, vi> L;
  vector<vector<pii>> A(N);

  rep(i, N) {
    ll m;
    cin >> m;

    rep(_, m) {
      ll p, e;
      cin >> p >> e;
      L[p].emplace_back(e);
      A[i].emplace_back(p, e);
    }
  }

  for (auto [p, l] : L)
    sort(all(L[p]));

  set<vector<pii>> S;
  ll flag = 0;

  rep(i, N) {
    vector<pii> l;

    for (auto [p, e] : A[i]) {
      if (L[p].back() == e) {
        if (L[p].size() >= 2) {
          ll a = *(L[p].end() - 2);
          if (a != e) {
            l.emplace_back(p, a);
          }
        } else {
          l.emplace_back(p, 0);
        }
      }
    }

    sort(all(l));
    S.emplace(l);
  }

  cout << S.size() << "\n";
}

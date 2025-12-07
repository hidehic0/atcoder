#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  cin >> N >> Q;

  ll cur = N;

  set<pii> S;
  S.emplace(LONG_LONG_MIN, LONG_LONG_MIN);
  S.emplace(LONG_LONG_MAX, LONG_LONG_MAX);

  while (Q--) {
    ll l, r;
    cin >> l >> r;

    auto it = prev(S.lower_bound(mp(l + 1, l + 1)));
    if (it->second < l)
      it++;

    ll nl = l, nr = r;
    ll res = r - l + 1;
    vpii T;

    while (it->first <= r) {
      ll tl, tr;
      tie(tl, tr) = *it;
      if (tl <= l) {
        nl = tl;
        tl = l;
      }
      if (tr >= r) {
        nr = tr;
        tr = r;
      }
      res -= tr - tl + 1;
      T.emplace_back(*it);
      it++;
    }

    for (auto [tl, tr] : T) {
      S.erase(mp(tl, tr));
    }
    S.emplace(nl, nr);
    cur -= res;
    cout << cur << "\n";
  }
}

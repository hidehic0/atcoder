#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "data-structure/range_set.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;

  vector<RangeSet> D(M + 1, RangeSet());
  rep(i, N) {
    ll a;
    cin >> a;

    ll l = (a < 0 ? (-a + i) / (i + 1) : 1);
    ll r = min(M + 1, (N - a + i) / (i + 1));

    for (int k = l; k < r; k++) {
      D[k].insert(a + (i + 1) * k);
    }
  }

  rep(i, M) { cout << D[i + 1].mex() << endl; }
}

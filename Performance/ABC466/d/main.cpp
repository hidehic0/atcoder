/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

si X[400000], Y[400000];

int main() {
  ll N, M;
  in(N, M);

  rep(_, M) {
    ll r, c;
    in(r, c);

    for (auto t : X[r]) {
      if (Y[t].contains(r))
        Y[t].erase(r);
    }

    X[r].clear();

    for (auto t : Y[c]) {
      if (X[t].contains(c))
        X[t].erase(c);
    }

    Y[c].clear();

    X[r].emplace(c), Y[c].emplace(r);
  }

  ll ans = 0;

  rep(i, 400000) ans += X[i].size();

  out(ans);
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

map<pii, pii> G, memo;

pii leader(pii p) {
  if (memo.contains(p))
    return memo[p];
  if (!G.contains(p))
    return memo[p] = p;
  else
    return memo[p] = leader(G[p]);
}

int main() {
  ll N;
  cin >> N;
  vi A(N), T(N);
  rep(i, N) cin >> A[i] >> T[i];
  ll Q;
  cin >> Q;
  vi X(Q);
  cin >> X;

  set<pii> S;
  rep(i, Q) S.emplace(X[i], 0);
  ll cur = 0;

  rep(i, N) {
    switch (T[i]) {
    case 1: {
      cur += A[i];
      break;
    }
    case 2: {
      A[i] -= cur;
      auto it = S.begin();
      vpii E;
      for (; it != S.end() && it->first < A[i]; it++) {
        G[*it] = mp(A[i], i + 1);
        E.emplace_back(*it);
      }

      if (!E.empty()) {
        for (auto p : E)
          S.erase(p);
        S.emplace(A[i], i + 1);
      }
      break;
    }
    case 3: {
      A[i] -= cur;
      auto it = S.rbegin();
      vpii E;
      for (; it != S.rend() && it->first > A[i]; it++) {
        G[*it] = mp(A[i], i + 1);
        E.emplace_back(*it);
      }

      if (!E.empty()) {
        for (auto p : E)
          S.erase(p);
        S.emplace(A[i], i + 1);
      }
      break;
    }
    }
  }

  rep(i, Q) { cout << leader(mp(X[i], 0)).first + cur << "\n"; }
}

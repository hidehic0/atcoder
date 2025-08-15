#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M, K;
  cin >> N >> M >> K;
  vector<ll> A(N);
  rep(i, N) cin >> A[i];

  ll cur = 0;
  multiset<ll> L, R;

  rep(i, M) {
    if (i < K) {
      L.insert(A[i]);
    } else {
      auto it = prev(L.end());
      if (*it > A[i]) {
        R.insert(*it);
        L.erase(it);
        L.insert(A[i]);
      } else {
        R.insert(A[i]);
      }
    }
  }

  auto it = L.begin();
  rep(_, K) {
    cur += *it;
    it++;
  }

  rep(i, N - M) {
    cout << cur << " ";
    if (L.find(A[i]) == L.end()) {
      R.erase(R.find(A[i]));
    } else {
      cur -= *L.find(A[i]);
      L.erase(L.find(A[i]));

      if (R.size() == 0) {
        L.insert(A[i + M]);
        cur += A[i + M];
        continue;
      }

      L.insert(*R.begin());
      cur += *R.begin();
      R.erase(R.begin());
    }

    if (*prev(L.end()) > A[i + M]) {
      cur -= *prev(L.end());
      R.insert(*prev(L.end()));
      L.erase(prev(L.end()));
      L.insert(A[i + M]);
      cur += A[i + M];
    } else {
      R.insert(A[i + M]);
    }
  }

  cout << cur << "\n";
}

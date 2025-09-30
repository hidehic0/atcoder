#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using mint = modint998244353;

int main() {
  ll N;
  string S;

  cin >> N >> S;
  mint ans = 0;

  map<int, mint> D;

  REP(i, 1, N) {
    if (N % i == 0) {
      vector<bool> l(i, true);
      rep(k, N) {
        if (S[k] == '.') {
          l[k % i] = false;
        }
      }

      mint cur = 1;

      rep(k, i) {
        if (l[k]) {
          cur *= 2;
        }
      }

      auto it = D.begin();
      while (it != D.end()) {
        if (i % (*it).first == 0) {
          cur -= (*it).second;
        }
        it++;
      }

      D[i] = cur;
      ans += cur;
    }
  }

  cout << ans.val() << "\n";
}

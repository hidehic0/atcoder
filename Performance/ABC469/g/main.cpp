/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll K;
  in(K);

  VC<str> S(K);
  in(S);
  vpii L;

  rep(i, K) {
    ll cur = 1, s = 0;

    for (auto s : S[i]) {
      if (s == 'a')
        s += cur;
      else
        cur *= -1;
    }

    L.emplace_back(s, cur);
  }

  ll N;
  string T;
  in(N, T);
}

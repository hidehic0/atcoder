/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  string S;
  in(S);
  int N = S.size();

  VC A(N, pii{-1, -1}), B(N, pii{-1, -1});

  auto add = [](pii &a, ll k) {
    if (a.first == -1)
      a.first = k;
    else if (a.second == -1)
      a.second = k;
  };

  rrep(i, S.size()) {
    rep(k, i, S.size()) {
      if (S[i] != S[k]) {
        dump(i, k);

        if ((i + k) & 1) {
          add(B[(i + k) / 2], i);
        } else {
          add(A[(i + k) / 2], i);
        }
      }
    }
  }

  int ans = 0;

  rep(i, S.size()) {
    dump(min<ll>(i - A[i].second + 1, min(N - i, i + 1)), A[i]);
    ans += min<ll>(i - A[i].second, min(N - i, i + 1));

    if (i < S.size() - 1) {
      ans += min<ll>(B[i].second == -1 ? N : i - B[i].second,
                     min(N - i - 1, i + 1));
    }
  }

  out(ans);
}

/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll N, Q;
  in(N, Q);
  vi A(N, 0), P(N, 0);

  mii D;
  D[0] = N;
  ll offset = 0, cur = 0;

  while (Q--) {
    ll t;
    in(t);

    if (t == 1) {
      ll x;
      in(x), x--;

      A[x] = max(A[x] - offset + P[x], 0LL);
      P[x] = offset;

      dump(A[x]);

      D[A[x]]--, D[A[x] + 1]++;
      cur ^= A[x] ^ (A[x] + 1);

      if (D[A[x]] == 0)
        D.erase(A[x]);

      A[x]++;
    } else {
      offset++;
      mii ND;
      ND[0] = D[0];

      for (auto [k, v] : D) {
        if (k == 0)
          continue;

        ND[k - 1] += D[k];

        if (v & 1)
          cur ^= k ^ (k - 1);
      }

      swap(ND, D);
    }

    out(cur);
  }
}

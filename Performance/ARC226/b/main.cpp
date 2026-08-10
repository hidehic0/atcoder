/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

void solve() {
  ll N, M;
  in(N, M);
  vi A(M);
  in(A);

  mii PQ;

  if (A.back() % N == 0) {
    PQ[(1LL << (M - 1)) * (A.back() / N)] = N;
  } else {
    ll x = A.back() % N;
    PQ[(1LL << (M - 1)) * (A.back() / N + 1LL)] = x;
    PQ[(1LL << (M - 1)) * (A.back() / N)] = N - x;
  }

  dump(A);

  rrep(i, M - 1) {
    ll t = 1LL << i;
    dump(i, PQ);

    while (A[i] > 0 && PQ.size() >= 2) {
      auto it = PQ.begin();
      ll x = ((next(it)->first) - it->first + t - 1) / t, cnt = it->second,
         f = it->first;

      PQ.erase(it);

      if (cnt * x >= A[i]) {
        if (A[i] % cnt == 0) {
          PQ[f + (A[i] / cnt) * t] += cnt;
        } else {
          ll x = A[i] % (it->second);
          PQ[f + (A[i] / cnt + 1) * t] += x;
          PQ[f + (A[i] / cnt) * t] += cnt - x;
        }

        A[i] = 0;
      } else {
        PQ[f + x * t] += cnt;
        A[i] -= cnt * x;
      }
    }

    if (A[i] == 0)
      continue;

    mii NPQ;
    auto it = PQ.begin();

    if (A[i] % N == 0) {
      NPQ[it->first + t * (A[i] / N)] = N;
    } else {
      ll x = A[i] % N;
      NPQ[it->first + t * (A[i] / N + 1)] = x;
      NPQ[it->first + t * (A[i] / N)] = N - x;
    }

    swap(PQ, NPQ);
    dump(i, PQ);
  }

  out(prev(PQ.end())->first);
}

int main() {
  ll T;
  in(T);

  while (T--)
    solve();
}

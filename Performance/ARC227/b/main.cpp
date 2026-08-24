/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

#include "data-structure/implicit_treap.hpp"

int main() {
  ll N;
  in(N);
  vi A(N);
  in(A);
  sort(all(A));

  ImplicitTreap<ll, [](ll a, ll b) { return a + b; }, []() { return 0; }> L;

  rep(i, N) {
    if (A[i] > i) {
      out("No");
      return 0;
    }

    L.insert(A[i], A[i]);
  }

  out("Yes");
  vi ans;
  rep(i, N) ans.emplace_back(L[i]);

  out(ans);
}

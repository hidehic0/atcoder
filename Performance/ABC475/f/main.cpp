/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll H, W;
  in(H, W);
  VC<str> S(H);
  in(S);

  if (H < W) {
    VC<str> NS(W);

    rep(k, W) NS[k].resize(H);

    rep(i, H) rep(k, W) NS[k][i] = S[i][k];

    swap(H, W), swap(S, NS);
  }

  vvi A(H, vi(W + 1, 0));

  ll ans = 1;

  rep(i, H) rep(k, W) A[i][k + 1] = A[i][k] + (S[i][k] == '.');

  rep(l, W) rep(r, l, W) {
    vpii L;
    vi X(H + 1, 0);

    rep(i, H) X[i + 1] += X[i] + (A[i][r + 1] != A[i][l]);

    L.emplace_back(0, 0);

    rep(i, H) {
      auto [a, b] = L.back();

      L.emplace_back(a + (S[i][l] == '.'), b + (S[i][r] == '.'));

      ll left = -1, right = L.size();

      while (right - left > 1) {
        ll mid = (left + right) >> 1;

        if (L[mid].first < L.back().first && L[mid].second < L.back().second)
          left = mid;
        else
          right = mid;
      }

      if (A[i][r + 1] != A[i][l]) {
        ans += X[left + 1];
      }
    }
  }

  out(ans);
}

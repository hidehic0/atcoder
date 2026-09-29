/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll N, M;
  in(N, M);
  vi A(N), B(N);
  in(A, B);

  vi XD(4 * N + 1, 0), XC(4 * N + 1, 0), YD(4 * N + 1, 0), YC(4 * N + 1, 0);

  rep(x, N) rep(y, N) {
    ll c = A[x] * B[y] % M;

    ll nx = (x + y) + 2 * N, ny = (x - y) + 2 * N;

    XD[nx + 1] += nx * c, XC[nx + 1] += c;
    YD[ny + 1] += ny * c, YC[ny + 1] += c;
  }

  rep(i, 4 * N) XD[i + 1] += XD[i];
  rep(i, 4 * N) XC[i + 1] += XC[i];
  rep(i, 4 * N) YD[i + 1] += YD[i];
  rep(i, 4 * N) YC[i + 1] += YC[i];

  ll ans = 0;

  rep(x, N) rep(y, N) {
    ll nx = (x + y) + 2 * N, ny = (x - y) + 2 * N;

    ll cnt = 0;
    cnt += nx * XC[nx] - XD[nx];
    cnt += XD.back() - XD[nx] - nx * (XC.back() - XC[nx]);
    cnt += ny * YC[ny] - YD[ny];
    cnt += YD.back() - YD[ny] - ny * (YC.back() - YC[ny]);

    // dump(cnt, x, y);
    cnt /= 2;

    ans ^= cnt + x * N + y;
  }

  out(ans);
}

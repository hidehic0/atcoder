/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

ll dp[520][5][2][2][1200];
bool T[520][5][2][2][1200];

string N;

ll rec(int k, int t, bool z, bool b, int used) {
  if (T[k][t][z][b][used]) {
    return dp[k][t][z][b][used];
  }
  if (k == N.size()) {
    int cur = 0;
    cur += t == 0;
    cur += popcount(uint32_t(used)) == 3;
    cur += (used >> 3) & 1;

    T[k][t][z][b][used] = true;
    return dp[k][t][z][b][used] = (cur == 1);
  }

  ll res = 0;

  ll n = N[k] - '0';

  rep(i, 10) {
    if (!b && i > n)
      break;

    int nu = used;

    if (z || i != 0)
      nu |= 1 << i;

    res += rec(k + 1, (t * 10 + i) % 3, z || i != 0, b || (i < n), nu);
    res %= 998244353;
  }

  dp[k][t][z][b][used] = res;
  T[k][t][z][b][used] = true;

  return dp[k][t][z][b][used];
}

int main() {
  in(N);
  si t;

  ll res = rec(0, 0, false, false, 0);
  res += 998244352;
  res %= 998244353;

  out(res);
}

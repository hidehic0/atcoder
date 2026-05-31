/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

const string B =
    "00000000000000000000000000000000000000000000000000000000000000000000000000"
    "00000000000000000000000000100011110001011101000001010100010000110000100100"
    "11010101010100111110010110001000010001110001000000100111001101010001110011"
    "11110100000111001100100011001000011110010011010000110101110011111011000011"
    "0010100110100100101101011001001001001";

int main() {
  ll H, W;
  in(H, W);

  vvvi dp(333, vvi(H, vi(W, 0)));

  rep(i, H) {
    string s;
    in(s);
    rep(k, W) {
      if (s[k] == '#')
        dp[0][i][k] = 1;
    }
  }

  rep(b, 332) {
    rep(i, H) {
      rep(k, W) {
        for (auto [mx, my] : MOVES2) {
          ll nx = mx + i, ny = my + k;

          if (coordinate_check(nx, ny, H, W)) {
            if (!dp[b][i][k])
              dp[b + 1][i][k] |= dp[b][nx][ny];
          }
        }
      }
    }
  }

  vvi P = dp.back();

  rrep(b, 332) {
    if (B[b] == '0')
      continue;

    vvi NP(H, vi(W, 0));

    rep(x, H) rep(y, W) {
      for (auto [mx, my] : MOVES2) {
        ll nx = x + mx, ny = y + my;

        if (coordinate_check(nx, ny, H, W) && P[x][y] == 0 && dp[b][nx][ny])
          NP[x][y] = 1;
      }
    }

    swap(P, NP);
  }

  dump(P);
  rep(i, H) {
    rep(k, W) {
      if (P[i][k] == '0')
        cout << '.';
      else
        cout << '#';

      if (k + 1 == W)
        cout << "\n";
    }
  }
}

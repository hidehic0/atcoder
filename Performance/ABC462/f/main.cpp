/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

/*
 置き換えを操作と呼ぶ
 dp[i][j] =
 (S[:i+1]を操作したときの文字列のなかで、S[:i+1]との部分文字列ABCが増えた個数がjのときの、操作回数の最小値)
 として考える

 最終的な文字列をS'とする
 遷移は、S'[i-2:i+1]がABCの場合は
   操作コストをyとしておく
   k=[0,3)でS[i-k-2:i-k+1]がABCの場合は、dp[i][j]=dp[i-3][j]+y（結局、元のABCを壊すか、そのままなので増加しない）
   そうでない場合は、dp[i][j] = dp[i-3][j-1]+y (壊しもしないので増加する)
 そうでない場合
   S[i-2:i+1]がABCの場合、dp[i][j]=dp[i-1][j+1]（元のABCが壊されてるので、一個減る）
   そうでない場合、dp[i][j]=dp[i][j]（もちろん減りもしない）

 とすればいい
 jがマイナスを管理しなくてもよいのは、もとのABCを壊したとき、一つ増えないと明らかに最適でないため
 */

void solve() {
  string S;
  ll K, N;
  in(S, K);

  N = S.size();

  vi C(N, 0),
      B(N,
        0); // C[i]=S[i-2:i+1]をABCに置き換えるときの操作コスト
            // B[i]=(k=[0,3)の範囲で、S[i-k-2:i-k+1]がABCになるものがあるかどうか)

  rep(i, 2, N) {
    if (S[i - 2] != 'A')
      C[i]++;
    if (S[i - 1] != 'B')
      C[i]++;
    if (S[i] != 'C')
      C[i]++;

    rep(k, 3) if (k + i < N) B[i + k] |= (C[i] == 0);
  }

  vvi dp(N + 1, vi(K + 1, 1e18));

  // 増えない場合は変えなくていいので操作コストが0
  rep(i, N + 1) dp[i][0] = 0;

  rep(i, N) {
    rep(k, K + 1) {
      if (k + (C[i] == 0) <= K)
        chmin(dp[i + 1][k], dp[i][k + (C[i] == 0)]);

      if (i >= 2)
        chmin(dp[i + 1][k], dp[i - 2][k - 1 + B[i]] + C[i]);
    }
  }

  dump(C, B);

  ll ans = dp.back().back();

  out(ans >= 1e18 ? -1 : ans);
}

int main() {
  ll T;
  in(T);

  while (T--)
    solve();
}

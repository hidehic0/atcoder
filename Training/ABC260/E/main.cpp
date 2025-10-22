#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, M;
  cin >> N >> M;

  vector<bool> used(N);
  vvi L(M);
  vi A(N), B(N), ans(M + 1, 0);

  rep(i, N) {
    cin >> A[i] >> B[i];
    A[i]--;
    B[i]--;
    L[A[i]].emplace_back(i);
    L[B[i]].emplace_back(i);
  }

  ll cnt = 0, right = 0;

  rep(left, M) {
    if (left > right) {
      cnt = 0;
      right = left;
    }

    while (right < M && cnt < N) {
      for (ll k : L[right]) {
        cnt += !used[k];
        used[k] = true;
      }

      right++;
    }

    if (cnt == N) {
      ans[right - left - 1]++;
      ans[M - right + (right - left)]--;
    }

    for (ll k : L[left]) {
      if (B[k] == left || B[k] >= right) {
        used[k] = false;
        cnt--;
      }
    }
  }

  rep(i, M) {
    ans[i + 1] += ans[i];
    cout << ans[i] << (i + 1 == M ? "\n" : " ");
  }
}

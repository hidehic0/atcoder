#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, M, L;
vi D;

map<tuple<ll, ll, ll>, bool> memo;

bool rec(ll bita, ll bitb, ll turn) {
  if (memo.contains(tie(bita, bitb, turn)))
    return memo[tie(bita, bitb, turn)];

  vi A, B, C;
  rep(i, D.size()) {
    if ((bita >> i) & 1)
      A.emplace_back(i);
    else if ((bitb >> i) & 1)
      B.emplace_back(i);
    else
      C.emplace_back(i);
  }

  if (turn == 0) {
    for (auto i : A) {
      for (auto k : C) {
        if (D[i] <= D[k])
          continue;

        if (!rec((bita ^ (1 << i)) | (1 << k), bitb, turn ^ 1))
          return memo[tie(bita, bitb, turn)] = true;
      }

      if (!rec(bita ^ (1 << i), bitb, turn ^ 1))
        return memo[tie(bita, bitb, turn)] = true;
    }
  } else {
    for (auto i : B) {
      for (auto k : C) {
        if (D[i] <= D[k])
          continue;

        if (!rec(bita, (bitb ^ (1 << i)) | (1 << k), turn ^ 1))
          return memo[tie(bita, bitb, turn)] = true;
      }

      if (!rec(bita, bitb ^ (1 << i), turn ^ 1))
        return memo[tie(bita, bitb, turn)] = true;
    }
  }

  return memo[tie(bita, bitb, turn)] = false;
}

int main() {
  cin >> N >> M >> L;
  vi A(N), B(M), C(L);

  cin >> A >> B >> C;
  rep(i, N) D.emplace_back(A[i]);
  rep(i, M) D.emplace_back(B[i]);
  rep(i, L) D.emplace_back(C[i]);

  ll bita = 0, bitb = 0;

  rep(i, N) bita |= (1 << i);
  REP(i, N, N + M) bitb |= (1 << i);

  if (rec(bita, bitb, 0))
    cout << "Takahashi";
  else
    cout << "Aoki";
  cout << "\n";
}

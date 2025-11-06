#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N;
string S, X;
map<pii, bool> memo;

bool rec(ll ind, ll cur) {
  if (memo.count(mp(ind, cur)) != 0)
    return memo[mp(ind, cur)];

  if (ind == N - 1) {
    if (X[ind] == 'A') {
      if ((cur * 10 + (S[ind] - '0')) % 7 == 0 && (cur * 10) % 7 == 0)
        return false;
      else
        return true;
    } else {
      if ((cur * 10 + (S[ind] - '0')) % 7 != 0 && (cur * 10) % 7 != 0)
        return false;
      else
        return true;
    }
  }

  if (rec(ind + 1, (cur * 10 + (S[ind] - '0')) % 7) == (X[ind] == X[ind + 1]))
    return memo[mp(ind, cur)] = true;
  if (rec(ind + 1, (cur * 10) % 7) == (X[ind] == X[ind + 1]))
    return memo[mp(ind, cur)] = true;

  return memo[mp(ind, cur)] = false;
}

int main() {
  input(N, S, X);
  bool res = rec(0, 0);

  if (X[0] == 'A') {
    res ^= 1;
  }

  cout << (res ? "Takahashi" : "Aoki") << "\n";
}

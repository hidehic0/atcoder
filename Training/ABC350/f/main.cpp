#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

string S;
mii D;

string rec(ll l, ll r, ll rev, ll sf) {
  vector<string> L;

  ll i = l;
  while (i < r) {
    if (S[i] == '(') {
      L.emplace_back(rec(i + 1, D[i], rev ^ 1, sf ^ 1));
      i = D[i];
    } else {
      string tmp = "";
      tmp += S[i];
      if (sf)
        tmp[0] ^= 0x20;

      L.emplace_back(tmp);
    }

    i++;
  }

  string ans;
  if (rev)
    reverse(all(L));

  for (string s : L)
    ans += s;

  return ans;
}

int main() {
  cin >> S;

  stack<ll> ST;

  rep(i, S.size()) {
    if (S[i] == '(') {
      ST.emplace(i);
    } else if (S[i] == ')') {
      D[ST.top()] = i;
      ST.pop();
    }
  }

  cout << rec(0, S.size(), false, false) << "\n";
}

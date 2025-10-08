#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

struct Node {
  ll par, x;
};

int main() {
  ll Q;
  cin >> Q;

  map<ll, ll> D;
  D[0] = 0;
  vector<Node> L = {Node{-1, -1}};

  ll cur = 0;

  REP(ind, 1, Q + 1) {
    string tp;
    cin >> tp;

    if (tp == "ADD") {
      ll x;
      cin >> x;

      L.emplace_back(Node{D[cur], x});
      D[cur] = L.size() - 1;
    } else if (tp == "DELETE") {
      if (L[D[cur]].par != -1) {
        D[cur] = L[D[cur]].par;
      }
    } else if (tp == "SAVE") {
      ll y;
      cin >> y;
      D[y] = D[cur];
    } else {
      ll y;
      cin >> y;
      D[cur] = D[y];
    }

    cout << L[D[cur]].x << (ind == Q ? "\n" : " ");
  }
}

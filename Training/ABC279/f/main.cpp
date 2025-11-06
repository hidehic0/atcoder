#include <bits/stdc++.h>
using namespace std;

#include "data-structure/unionfind.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  cin >> N >> Q;

  ll m = N + N, bcnt = N;

  vi lavel(N + N + Q, -1), ball_ind(N + Q), last_box(N);
  UnionFind UF(N + N + Q);

  rep(i, N) {
    UF.merge(i, i + N);
    lavel[i] = i;
    lavel[i + N] = i;
    ball_ind[i] = i + N;
    last_box[i] = i;
  }

  while (Q--) {
    ll t;
    cin >> t;

    if (t == 1) {
      ll x, y;
      cin >> x >> y;
      x--;
      y--;

      if (lavel[UF.leader(last_box[y])] != y)
        continue;

      if (lavel[UF.leader(last_box[x])] != x) {
        last_box[x] = m;
        lavel[UF.leader(last_box[y])] = x;
        lavel[m] = x;
        UF.merge(last_box[y], m);
        m++;
      } else {
        lavel[UF.leader(last_box[y])] = x;
        UF.merge(last_box[x], last_box[y]);
      }
    } else if (t == 2) {
      ll x;
      cin >> x;
      x--;

      lavel[m] = x;
      ball_ind[bcnt] = m;

      if (lavel[UF.leader(last_box[x])] != x) {
        m++;
        lavel[m] = x;
        last_box[x] = m;
        UF.merge(m, m - 1);
      } else {
        UF.merge(last_box[x], m);
      }

      m++;
      bcnt++;
    } else {
      ll x;
      cin >> x;

      cout << lavel[UF.leader(ball_ind[x - 1])] + 1 << "\n";
    }
  }
}

#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

void question(ll a, ll b) { cout << "? " << a << " " << b << endl; }

int main() {
  ll N;
  cin >> N;

  vvi D(200);
  ll ans = 1e18;

  REP(i, 3, N + 1) {
    ll a, b;
    question(1, i);
    cin >> a;
    question(2, i);
    cin >> b;

    D[a + b].emplace_back(i);
    chmin(ans, a + b);
  }

  if (ans != 3)
    cout << "! " << ans << "\n";
  else {
    if (D[ans].size() != 2) {
      cout << "! 1" << "\n";
      return 0;
    }
    question(D[ans][0], D[ans][1]);
    ll a;
    cin >> a;
    cout << "! ";
    if (a == 1) {
      cout << 3;
    } else {
      cout << 1;
    }
    cout << endl;
  }
}

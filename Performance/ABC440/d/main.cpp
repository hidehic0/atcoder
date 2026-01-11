#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, Q;
  cin >> N >> Q;
  vi A(N);
  cin >> A;
  sort(all(A));

  while (Q--) {
    ll x, y;
    cin >> x >> y;

    ll left = x - 1, right = 1e11;
    while (right - left > 1) {
      ll mid = (left + right) / 2;
      ll a = upper_bound(all(A), mid) - A.begin();
      ll b = upper_bound(all(A), x - 1) - A.begin();

      if ((mid - x + 1) - (a - b) < y)
        left = mid;
      else
        right = mid;
    }

    cout << right << "\n";
  }
}

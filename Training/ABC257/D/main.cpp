#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N;
  cin >> N;

  vi P(N);
  vpii L(N);

  rep(i, N) cin >> L[i].first >> L[i].second >> P[i];

  ll left = -1, right = 1e10;

  while (abs(right - left) > 1) {
    ll mid = (left + right) / 2;
    bool flag = false;

    rep(i, N) {
      vector<bool> used(N, false);
      used[i] = true;

      queue<ll> Q;
      Q.emplace(i);

      while (!Q.empty()) {
        ll cur = Q.front();
        Q.pop();

        rep(nxt, N) {
          if (used[nxt])
            continue;

          ll dis = llabs(L[cur].first - L[nxt].first) +
                   llabs(L[cur].second - L[nxt].second);

          if (dis <= P[cur] * mid) {
            used[nxt] = true;
            Q.emplace(nxt);
          }
        }
      }

      bool f = true;

      rep(k, N) {
        if (!used[k]) {
          f = false;
          break;
        }
      };

      if (f) {
        flag = true;
        break;
      }
    }

    if (flag) {
      right = mid;
    } else {
      left = mid;
    }
  }

  cout << right << "\n";
}

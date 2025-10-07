#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll H, W, N;
  cin >> H >> W >> N;
  vi hmax(H, 0), wmax(W, 0), ans(N, -1);

  map<ll, vector<tuple<ll, ll, ll>>> L;

  rep(i, N) {
    ll r, c, a;
    cin >> r >> c >> a;
    r--;
    c--;

    L[a].emplace_back(r, c, i);
  }

  auto it = L.rbegin();

  while (it != L.rend()) {
    auto l = (*it).second;

    vector<pii> uh, uw;

    for (auto [h, w, ind] : l) {
      ll n = max(hmax[h], wmax[w]);
      ans[ind] = n;
    }

    for (auto [h, w, ind] : l) {
      chmax(hmax[h], ans[ind] + 1);
      chmax(wmax[w], ans[ind] + 1);
    }

    it++;
  }

  rep(i, N) { cout << ans[i] << "\n"; }
}

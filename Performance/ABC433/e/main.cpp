#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

using TP = tuple<ll, ll, bool,
                 bool>; // x,y,x側の条件を満しているか,y側の条件を満しているか

optional<vvi> solve(ll N, ll M, vi const &X, vi const &Y) {
  vvi res(N, vi(M, -1));
  VC<VC<TP>> L(N * M);

  rep(i, N) {
    rep(k, M) {
      ll t = min(X[i], Y[k]) - 1;
      L[t].emplace_back(i, k, false, false);
    }
  }

  vb usedx(N, false), usedy(M, false);
  queue<TP> Q;

  rrep(t, N * M) {
    ll cnt = 0;

    queue<TP> PQ;

    rep(i, L[t].size()) {
      ll x, y;
      bool a, b;

      tie(x, y, a, b) = L[t][i];

      a |= usedx[x];
      b |= usedy[y];

      L[t][i] = tie(x, y, a, b);

      if (!(a || b)) {
        PQ.emplace(L[t][i]);
      } else {
        Q.emplace(L[t][i]);
      }
    }

    if ((PQ.empty() && Q.empty()))
      return nullopt;

    if (!PQ.empty()) {
      ll x, y;
      bool a, b;
      tie(x, y, a, b) = PQ.front();
      PQ.pop();

      res[x][y] = t + 1;

      if (X[x] - 1 == t)
        usedx[x] = true;

      if (Y[y] - 1 == t)
        usedy[y] = true;

      while (!PQ.empty()) {
        tie(x, y, a, b) = PQ.front();
        PQ.pop();

        Q.emplace(x, y, a, b);
      }
    } else {
      ll x, y;
      bool a, b;
      tie(x, y, a, b) = Q.front();
      Q.pop();

      res[x][y] = t + 1;
    }
  }

  return res;
}

int main() {
  ll T;
  cin >> T;

  while (T--) {
    ll N, M;
    cin >> N >> M;

    vi X(N), Y(M);
    input(X);
    input(Y);

    auto res = solve(N, M, X, Y);

    if (!res) {
      cout << "No" << "\n";
      continue;
    }
    cout << "Yes" << "\n";

    rep(i, N) {
      rep(k, M) { cout << res.value()[i][k] << (k + 1 == M ? "\n" : " "); }
    }
  }
}

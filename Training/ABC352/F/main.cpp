#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll N, M;
vvpii G;

pair<ll, vi> get_rank(ll p, ll r) {
  vi used(N, -1);
  vi l = {p};

  ll res = 1 << r;
  used[p] = r;
  queue<ll> Q;
  Q.emplace(p);

  while (!Q.empty()) {
    ll cur = Q.front();
    Q.pop();

    for (auto [nxt, w] : G[cur]) {
      if (used[nxt] == -1) {
        if (used[cur] + w < 0 || used[cur] + w >= N)
          return mp(-1, used);

        l.emplace_back(nxt);
        used[nxt] = used[cur] + w;
        res |= 1 << used[nxt];
        Q.emplace(nxt);
      }
    }
  }

  return mp(res, used);
}

int main() {
  cin >> N >> M;
  G.resize(N);

  rep(_, M) {
    ll a, b, c;
    cin >> a >> b >> c;
    a--;
    b--;

    G[a].emplace_back(b, -c);
    G[b].emplace_back(a, c);
  }

  VC<VC<pair<ll, vi>>> L;
  vb used(N, false);

  rep(i, N) {
    if (used[i])
      continue;

    L.emplace_back(VC<pair<ll, vi>>{});

    rep(k, N) {
      auto t = get_rank(i, k);

      rep(p, N) {
        if (t.second[p] != -1)
          used[p] = true;
      }

      if (t.first != -1) {
        L.back().emplace_back(t);
      }
    }
  }

  vvi ldp(L.size() + 1, vi(1 << N, 0)), rdp(L.size() + 1, vi(1 << N, 0));
  ldp[0][0] = 1;
  rdp.back()[0] = 1;

  rrep(i, L.size()) {
    rep(bit, 1 << N) {
      rep(k, L[i].size()) {
        if ((bit & L[i][k].first) == 0) {
          rdp[i][bit | L[i][k].first] += rdp[i + 1][bit];
        }
      }
    }
  }

  vi ans(N, -1);

  rep(i, L.size()) {
    vvi T;
    ll su = 0;

    rep(k, L[i].size()) {
      ll cur = 0;

      rep(bit, 1 << N) {
        if ((bit & L[i][k].first) == 0) {
          cur += rdp[i + 1][(1 << N) - (bit | L[i][k].first) - 1] * ldp[i][bit];
        }
      }

      su += cur;
      if (cur >= 1) {
        T.emplace_back(L[i][k].second);
      }
    }

    if (T.size() == 1) {
      rep(k, N) {
        if (T.front()[k] != -1)
          ans[k] = T.front()[k] + 1;
      }
    }

    rep(bit, 1 << N) {
      rep(k, L[i].size()) {
        if ((bit & L[i][k].first) == 0) {
          ldp[i + 1][bit | L[i][k].first] += ldp[i][bit];
        }
      }
    }
  }

  out(ans);
}

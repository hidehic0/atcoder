/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll N, M, K;
  in(N, M, K);
  string T;
  VC<string> S(N);
  in(T, S);

  auto f = [&](ll ind) {
    vi res;

    rep(k, K) {
      if (S[ind][k] == T[k])
        res.emplace_back(1);
      else
        res.emplace_back(0);
    }

    return res;
  };

  VC<array<ll, 2>> ch(1);
  vi cnt(1, 0);
  ch[0] = {-1, -1};

  auto add = [&](const vi &X) {
    ll cur = 0;

    for (auto s : X) {
      cnt[cur]++;

      if (ch[cur][s] == -1) {
        ch[cur][s] = ch.size();
        ch.push_back({-1, -1});
        cnt.emplace_back(0);
      }

      cur = ch[cur][s];
    }

    cnt[cur]++;
  };
  auto del = [&](const vi &X) {
    ll cur = 0;

    for (auto s : X)
      cnt[cur]--, cur = ch[cur][s];

    cnt[cur]--;
  };

  rep(i, N) add(f(i));

  ll Q;
  in(Q);

  while (Q--) {
    ll x, y;
    in(x, y), --x, --y;

    del(f(x));
    S[x][y] = S[x][y] == 'x' ? 'o' : 'x';
    add(f(x));

    ll m = 0, cur = 0;
    vi v;

    rep(_, K) {
      if (cur == -1)
        break;

      if (ch[cur][1] == -1 || cnt[ch[cur][1]] + m <= M) {
        if (ch[cur][1] != -1)
          m = cnt[ch[cur][1]] + m;

        v.emplace_back(1);
        cur = ch[cur][0];
      } else {
        v.emplace_back(0);
        cur = ch[cur][1];
      }
    }

    bool flag = false;

    rep(i, v.size()) {
      if (v[i] == 0 && S[x][i] != T[i])
        break;

      if (v[i] == 1 && S[x][i] == T[i])
        flag = true;
    }

    if (flag)
      out("Yes");
    else
      out("No");
  }
}

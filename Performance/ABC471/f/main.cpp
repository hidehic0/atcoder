/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

int main() {
  ll N, K;
  in(N, K);
  VC<string> S(N);
  in(S);

  {
    bool flag = true;

    rep(i, N) rep(k, S[i].size()) if (S[i][k] != '0') flag = false;

    if (flag) {
      out(0);
      return 0;
    }
  }

  VC<VC<str>> D(11);
  vvb used(11);
  vi A(11, 0);

  rep(i, S.size()) D[S[i].size()].emplace_back(S[i]);

  A.back() = K;

  rrep(i, 1, 11) {
    used[i].resize(D[i].size(), false);

    ll m = min<ll>(A[i], D[i].size());

    A[i - 1] += A[i] - m, A[i] = m;
  }

  string ans;

  auto f = [](tuple<ll, str, ll> a, tuple<ll, str, ll> b) {
    auto [al, an, _] = a;
    auto [bl, bn, _] = b;

    if (al != bl) {
      return al > bl ? a : b;
    }

    for (int k = 0; k < min(an.size(), bn.size()); k++) {
      if (an[k] != bn[k]) {
        return an[k] > bn[k] ? a : b;
      }
    }

    return an.size() < bn.size() ? a : b;
  };

  {
    tuple<ll, str, ll> mx = {-1e18, "", -1e18};

    rep(i, N) {
      ll n = stoll(S[i]);

      if (A[S[i].size()]) {
        mx = f(mx, {-(S[i].size() - to_string(n).size()), to_string(n), i});
      } else {
        int k;

        for (k = 0; k < 11; k++) {
          if (A[k] != 0) {
            mx = f(mx, {to_string(n).size() - k, to_string(n), i});
            break;
          }
        }
      }
    }

    K--;

    auto [_, n, ind] = mx;
    ll l = S[ind].size();
    ans += n;

    rep(k, D[l].size()) {
      if (D[l][k] == S[ind]) {
        used[l][k] = true;
        break;
      }
    }

    if (A[l]) {
      A[l]--;
    } else {
      rep(k, 11) {
        if (A[k]) {
          A[k]--;
          break;
        }
      }
    }
  }

  set<tuple<str, ll, ll>, decltype([](const tuple<str, ll, ll> a,
                                      const tuple<str, ll, ll> b) -> bool {
        auto [as, _aa, _ab] = a;
        auto [bs, _ba, _bb] = b;

        str x = as + bs, y = bs + as;

        return x == y ? tie(_aa, _ab) < tie(_ba, _bb) : x < y;
      })>
      PQ;

  rep(i, 11) {
    if (!A[i])
      continue;

    rep(k, D[i].size()) {
      if (!used[i][k]) {
        PQ.emplace(D[i][k], i, k);
      }
    }
  }

  while (K--) {
    auto it = prev(PQ.end());

    auto [n, a, b] = *it;
    PQ.erase(it);

    used[a][b] = true, ans += D[a][b], A[a]--;

    if (A[a] == 0) {
      rep(k, D[a].size()) {
        if (used[a][k])
          continue;

        PQ.erase({D[a][k], a, k});
      }
    }
  }

  out(ans);
}

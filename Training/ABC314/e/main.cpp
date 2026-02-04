/**
 library: https://github.com/hidehic0/library_cpp
**/
#include <bits/stdc++.h>
using namespace std;

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#else
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#endif

#include "templates/alias.hpp"
#include "templates/macro.hpp"

struct R {
  ld c, p;
  vi l;
};

int main() {
  ll N, M;
  cin >> N >> M;
  VC<R> L;

  rep(i, N) {
    ll C, P;
    cin >> C >> P;
    vi S(P);
    cin >> S;

    L.emplace_back(R{(ld)C, (ld)P, S});
  }

  VC<ld> dp(M + 1, 1e9);
  dp[M] = 0;

  rrep(i, M) {
    rep(k, N) {
      ld z = 0, cur = 0;
      for (auto s : L[k].l) {
        if (s == 0)
          z += 1;
        else if (i + s <= M)
          cur += dp[min(i + s, M)];
      }

      cur /= L[k].p - z;
      if (L[k].p != z) {
        cur += L[k].c / (L[k].p - z) * L[k].p;
        if (i == 0)
          dump(k, cur, ((L[k].p - z)));
      }

      if (dp[i] > cur)
        dp[i] = cur;
    }
  }
  // dump(dp);

  cout << fixed << setprecision(15) << dp[0] << "\n";
}

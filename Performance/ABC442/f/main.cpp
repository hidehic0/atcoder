#include <bits/stdc++.h>
using namespace std;
#include <atcoder/segtree>
using namespace atcoder;

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

ll op(ll a, ll b) { return min(a, b); }
ll e() { return 1e18; }

int main() {
  ll N;
  cin >> N;
  VC<string> S(N);
  cin >> S;

  vi dp(N + 1, 1e18);
  dp[N] = 0;

  rep(i, N) {
    ll cur = 0;
    ll p = 1e18;
    vi L(N + 1);

    rrep(k, N + 1) {
      chmin(p, dp[k]);
      L[k] = p;
      cur += S[i][k] == '.';
    }
    vi nxt(N + 1, 1e18);

    rep(k, N + 1) {
      nxt[k] = cur + L[k];
      if (k < N) {
        cur += S[i][k] == '#';
        cur -= S[i][k] == '.';
      }
    }

    dp = nxt;
  }

  cout << *min_element(all(dp)) << "\n";
}

/**
 library: https://github.com/hidehic0/library_cpp
**/
#include <bits/stdc++.h>
using namespace std;
#include <atcoder/string>
using namespace atcoder;

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#else
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#endif

#include "segtree/dualsegtree.hpp"
#include "templates/alias.hpp"
#include "templates/macro.hpp"

ll op(ll a, ll b) { return min(a, b); }
ll e() { return 1e18; }

int main() {
  string S, T;
  cin >> S >> T;

  string P = S + T;

  auto L = z_algorithm(P);

  DualSegmentTree<ll, op, e> seg(T.size() + 1);
  seg.apply(0, 1, 0);
  ll ans = 1e18;

  rep(i, T.size()) {
    ll t = min((ll)L[i + S.size()], (ll)S.size());
    dump(i, t, seg.get(i));
    if (t == 0)
      continue;

    if (i + t + 1 > T.size())
      chmin(ans, seg.get(i) + 1);
    seg.apply(i + 1, min(i + t, (ll)T.size()) + 1, seg.get(i) + 1);
  }

  cout << (ans == 1e18 ? -1 : ans) << "\n";
}

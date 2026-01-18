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

ll op(ll a, ll b) { return a + b; }
ll e() { return 0; }

int main() {
  ll N, M = 5e5 + 10;
  cin >> N;
  string S;
  cin >> S;

  ll A = 0, B = 0;

  rep(i, N) {
    if (S[i] == 'A')
      A++;
    else if (S[i] == 'B')
      B++;
  }

  segtree<ll, op, e> seg(2e6);

  ll ans = 0;

  rrep(i, N) {
    seg.set(B - A + M, seg.get(B - A + M) + 1);
    if (S[i] == 'A')
      A--;
    else if (S[i] == 'B')
      B--;

    ans += seg.prod(0, -A + B + M);
  }

  cout << ans << "\n";
}

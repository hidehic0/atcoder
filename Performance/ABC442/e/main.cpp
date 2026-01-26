#include <bits/stdc++.h>
using namespace std;
#include <atcoder/all>
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

int main() {
  ll N, Q;
  cin >> N >> Q;
  VC<ld> L;

  rep(i, N) {
    ld a, b;
    cin >> a >> b;
    L.emplace_back(atan2l(a, b));
  }

  VC<ld> S = L;
  sort(all(S));

  while (Q--) {
    ll a, b;
    cin >> a >> b;
    a--, b--;

    if (L[a] <= L[b]) {
      cout << upper_bound(all(S), L[b]) - lower_bound(all(S), L[a]) << "\n";
      continue;
    }

    cout << S.end() - lower_bound(all(S), L[a]) + upper_bound(all(S), L[b]) -
                S.begin()
         << "\n";
  }
}

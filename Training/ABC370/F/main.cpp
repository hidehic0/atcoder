/**
 library: https://github.com/hidehic0/library_cpp
**/
#include <algorithm>
#include <array>
#include <cassert>
#include <chrono>
#include <climits>
#include <clocale>
#include <cmath>
#include <functional>
#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <ostream>
#include <queue>
#include <ranges>
#include <set>
#include <stack>
#include <string>
#include <tuple>
#include <vector>
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
#define export_command
#else
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#endif

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  ll N, K;
  cin >> N >> K;
  vi A(N);
  cin >> A;
  rep(i, N) A.emplace_back(A[i]);

  auto check = [&](ll k) {
    vvi dp(19, vi(N * 2, 1e10));
    ll right = 0, cur = 0;

    rep(left, N) {
      if (right < left)
        right = left, cur = 0;

      while (right < N * 2 && cur < k)
        cur += A[right], right++;

      if (cur < k)
        break;
      dp[0][left] = right;
      cur -= A[left];
    }

    right = 0, cur = 0;
    rep(left, N, N * 2) {
      if (right < left)
        right = left, cur = 0;

      while (right < N * 2 && cur < k)
        cur += A[right], right++;

      if (cur < k)
        break;
      dp[0][left] = right;
      cur -= A[left];
    }

    rep(b, 18) {
      rep(i, N * 2) {
        if (dp[b][i] >= (ll)A.size())
          continue;

        dp[b + 1][i] = dp[b][dp[b][i]];
      }
    }
    // dump(dp);

    ll res = 0;

    rep(st, N) {
      ll cur = st;

      rrep(b, 19) {
        if ((K >> b) & 1) {
          if (cur >= (ll)A.size())
            break;
          cur = dp[b][cur];
        }
      }

      if (cur <= (ll)(N + (ll)st))
        res++;
    }

    return res;
  };

  ll ng = 0, ok = 1e10;

  while (ok - ng > 1) {
    ll mid = (ng + ok) / 2;

    if (check(mid) > 0)
      ng = mid;
    else
      ok = mid;
  }

  cout << ng dms N - check(ng) << "\n";
}

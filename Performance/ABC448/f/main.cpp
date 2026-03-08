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
  ll N;
  cin >> N;
  vpii L(N);
  cin >> L;
  vi A(N);
  rep(i, N) A[i] = i;

  ll M = 76923;

  sort(all(A), [&](ll a, ll b) {
    if (L[a].first / M != L[b].first / M)
      return L[a].first < L[b].first;
    if (L[a].first / M % 2)
      return L[a].second > L[b].second;
    return L[a].second < L[b].second;
  });

  vi ans = {};

  rrep(i, N) if (A[i] != 0) ans.emplace_back(A[i] + 1);
  ans.emplace_back(1);
  reverse(all(ans));
  out(ans);
}

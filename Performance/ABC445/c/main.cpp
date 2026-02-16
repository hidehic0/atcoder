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

int dp[333][500000];

int main() {
  ll N;
  cin >> N;
  vi A(N);
  cin >> A;
  string T =
      "000000000000000000000000000000000000000000000000000000000000000000000000"
      "000000000000000000000000000010001111000101110100000101010001000011000010"
      "010011010101010100111110010110001000010001110001000000100111001101010001"
      "110011111101000001110011001000110010000111100100110100001101011100111110"
      "110000110010100110100100101101011001001001001";

  rep(i, N) { dp[0][i] = A[i] - 1; };

  rep(k, 1, 333) {
    rep(i, N) { dp[k][i] = dp[k - 1][dp[k - 1][i]]; }
  }

  rep(i, N) {
    ll cur = i;
    rrep(b, 333) {
      if (T[b] == '1') {
        cur = dp[b][cur];
      }
    }

    cout << cur + 1 << (i + 1 == N ? "\n" : " ");
  }
}

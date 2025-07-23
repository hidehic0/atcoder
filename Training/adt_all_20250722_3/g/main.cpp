#pragma GCC target("avx512f")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#line 1 "main.cpp"
#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#line 6 "/home/hidehic0/src/github.com/hidehic0/library_cpp/templates/alias.hpp"

using ll = long;
using ld = long double;
using vi = std::vector<long long>;
using vvi = std::vector<std::vector<long long>>;
using si = std::set<long long>;
using mii = std::map<long long, long, long>;
template <typename T> using V = std::vector<T>;
const std::string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string lowerlist = "abcdefghijklmnopqrstuvwxyz";
#define mp make_pair
#define dms << " " <<
#line 3 "/home/hidehic0/src/github.com/hidehic0/library_cpp/templates/macro.hpp"

#define rep(i, n) for (ll i = 0; i < (int)(n); i++)
#define REP(i, a, b) for (ll i = (int)(a); i < (int)(b); ++i)
#define all(a) (a).begin(), (a).end()

template <typename T> bool chmin(T &a, T b) {
  if (a > b) {
    a = b;
    return true;
  }
  return false;
}
template <typename T> bool chmax(T &a, T b) {
  if (a < b) {
    a = b;
    return true;
  }
  return false;
}

void YN(bool b) { std::cout << (b ? "Yes" : "No") << std::endl; }
void YE(bool b) {
  if (b) {
    std::cout << "Yes" << std::endl;
    exit(1);
  }
}
void NE(bool b) {
  if (b) {
    std::cout << "No" << std::endl;
    exit(1);
  }
}
#line 8 "main.cpp"

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll N;
  cin >> N;
  map<ll, ll> D;
  set<ll> Q;

  rep(_, N) {
    ll s, c;
    cin >> s >> c;
    D[s] = c;
    Q.emplace(s);
  }

  ll ans = 0;

  while (!Q.empty()) {
    ll s = *Q.begin();
    ans += D[s] % 2;
    D[s * 2] += D[s] / 2;
    if (D[s * 2] > 0) {
      Q.emplace(s * 2);
    }
    Q.erase(s);
  }

  cout << ans << endl;
}

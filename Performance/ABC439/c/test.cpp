#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

#line 1 "main.cpp"
#include <bits/stdc++.h>
using namespace std;

#line 6 "/home/hidehic0/src/github.com/hidehic0/library_cpp/templates/alias.hpp"

template <typename T> using VC = std::vector<T>;
using ll = long long;
using ld = long double;
using pii = std::pair<ll, ll>;
using vi = VC<ll>;
using vvi = VC<vi>;
using vvvi = VC<vvi>;
using vb = VC<bool>;
using vvb = VC<vb>;
using vf = VC<double>;
using vvf = VC<vf>;
using vpii = VC<pii>;
using vvpii = VC<vpii>;
using si = std::set<ll>;
using spii = std::set<pii>;
using mii = std::map<ll, ll>;
const std::string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string lowerlist = "abcdefghijklmnopqrstuvwxyz";
#define mp make_pair
#define dms << " " <<

constexpr int MOD998 = 998244353;
#line 4 "/home/hidehic0/src/github.com/hidehic0/library_cpp/templates/macro.hpp"

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rrep(i, n) for (int i = n - 1; i >= 0; i--)
#define REP(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define RREP(i, a, b) for (int i = (int)(b - 1); i >= (int)(a); i--)
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

template <typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
  is >> p.first >> p.second;
  return is;
}

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
  for (T &in : v)
    is >> in;
  return is;
}

template <typename T>
std::ostream &operator>>(std::ostream &os, const std::vector<T> &v) {
  for (int i = 0; i < (int)v.size(); i++) {
    os << v[i] << (i + 1 == v.size() ? "" : " ");
  }
  return os;
}

template <typename T> inline T ceil_div(T a, T b) { return (a + b - 1) / b; }
template <typename T> inline T mod_pow(T a, T n, T mod) {
  T res = 1;
  while (n) {
    if (n % 2 != 0) {
      res *= a;
      res %= mod;
    }

    a *= a;
    a %= mod;

    n >>= 1;
  }

  return res;
}

template <typename T> void apply_vec(std::vector<T> &v, T (*fn)(T)) {
  for (int i = 0; i < v.size(); i++)
    v[i] = fn(v[i]);
}
#line 6 "main.cpp"

int main() {
  ll N;
  cin >> N;
  si S, used;

  for (ll x = 1; x <= 4000; x++) {
    for (ll y = x + 1; y <= 4000; y++) {
      if (x * x + y * y <= N) {
        if (S.contains(x * x + y * y)) {
          S.erase(x * x + y * y);
        }
        if (!used.contains(x * x + y * y)) {
          S.emplace(x * x + y * y);
          used.emplace(x * x + y * y);
        }
      }
    }
  }

  cout << S.size() << "\n";
  for (auto l : S)
    cout << l << " ";
  cout << "\n";
}

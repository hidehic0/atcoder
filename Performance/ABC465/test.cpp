
#line 1 "main.cpp"
/**
 library: https://github.com/hidehic0/library_cpp
**/
#line 1 "/home/hidehic0/src/github.com/hidehic0/library_cpp/all.h"
#if __has_include(<atcoder/all>)
#include <atcoder/all>
#endif

#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#elif __has_include(<cpp-dump/cpp-dump.hpp>)
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#endif

#line 7 "/home/hidehic0/src/github.com/hidehic0/library_cpp/templates/alias.hpp"

template <class T> using VC = std::vector<T>;
template <class T>
using rpriority_queue = std::priority_queue<T, VC<T>, std::greater<T>>;
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

// 引数の長さで内容が変わるrep 参考: https://trap.jp/post/1224
#define overload4(a, b, c, d, ...) d
#define _rep(i, n) for (int i = 0; i < (int)(n); i++)
#define REP(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define rep(...) overload4(__VA_ARGS__, REP, _rep)(__VA_ARGS__)
#define _rrep(i, n) for (int i = n - 1; i >= 0; i--)
#define RREP(i, a, b) for (int i = (int)(b - 1); i >= (int)(a); i--)
#define rrep(...) overload4(__VA_ARGS__, RREP, _rrep)(__VA_ARGS__)

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
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    os << v[i] << (i + 1 == v.size() ? "" : " ");
  }
  return os;
}

// pythonのprintライクな関数 参考:
// https://nyaannyaan.github.io/library/template/inout.hpp
inline void out() { std::cout << std::endl; }
template <typename T, typename... U, char sep = ' '>
void out(const T &t, const U &...u) {
  std::cout << t;

  if (sizeof...(u))
    std::cout << sep;

  out(u...);
}

// cinの短縮関数 参考: https://nyaannyaan.github.io/library/template/inout.hpp
inline void in() {}
template <typename T, class... U> void in(T &t, U &...u) {
  std::cin >> t;
  in(u...);
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
template <typename T> inline T minus_mod(T a, T b) { return ((a % b) + b) % b; }

template <typename T> void apply_vec(std::vector<T> &v, T (*fn)(T)) {
  for (int i = 0; i < v.size(); i++)
    v[i] = fn(v[i]);
}

template <typename T, class Comp> struct Top2 {
  T a, b;

  Top2() {}
  Top2(T a) : a(a) {}
  Top2(T a, T b) : a(a), b(b) {}

  void add(const T &v) {
    if (Comp{}(v, a))
      b = a, a = v;
    else if (Comp{}(v, b))
      b = v;
  }

  friend Top2<T, Comp> operator*(const Top2<T, Comp> &lhs,
                                 const Top2<T, Comp> &rhs) {
    auto n = lhs;
    n.add(rhs.a), n.add(rhs.b);

    return n;
  }

  Top2<T, Comp> &operator*=(const Top2<T, Comp> &rhs) {
    (*this) = (*this) * rhs;

    return *this;
  }
};

template <typename T> struct TopMin2 : public Top2<T, std::less<T>> {
  using Top2<T, std::less<T>>::Top2;
};

template <typename T> struct TopMax2 : public Top2<T, std::greater<T>> {
  using Top2<T, std::greater<T>>::Top2;
};
#line 30 "/home/hidehic0/src/github.com/hidehic0/library_cpp/all.h"

#line 3 "/home/hidehic0/src/github.com/hidehic0/library_cpp/grid/template.hpp"

bool coordinate_check(int x, int w, int H, int W) {
  return 0 <= x && x < H && 0 <= w && w < W;
}

constexpr std::array<std::pair<int, int>, 4> MOVES1 = {
    {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}};
constexpr std::array<std::pair<int, int>, 8> MOVES2 = {
    {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {-1, -1}, {1, -1}, {-1, 1}}};
#line 32 "/home/hidehic0/src/github.com/hidehic0/library_cpp/all.h"

#line 5 "/home/hidehic0/src/github.com/hidehic0/library_cpp/utils/compress.hpp"

template <class T> std::map<T, int> compress_1d(std::vector<T> V) {
  sort(V.begin(), V.end());
  V.erase(std::unique(V.begin(), V.end()), V.end());

  std::map<T, int> res;

  for (int i = 0; i < V.size(); i++) {
    res[V[i]] = i;
  }

  return res;
}
#line 5 "/home/hidehic0/src/github.com/hidehic0/library_cpp/utils/factorial.hpp"

template <class T> std::vector<T> factorial_list(int N) {
  std::vector<T> P(N + 1, 1);
  for (int i = 1; i <= N; i++) {
    P[i] = P[i - 1] * T{i};
  }

  return P;
}

template <class T> struct Fact {
  std::vector<T> F, FINV;
  int _n;

  Fact(int n) : F(n + 1, 1), FINV(n + 1, 1), _n(n) {
    rep(i, 1, n + 1) {
      F[i] = F[i - 1] * (T)i;
      FINV[i] = (T)1 / F[i];
    }
  }

  T *begin() { return F.begin(); }
  T *end() { return F.end(); }
  T *rbegin() { return F.rbegin(); }
  T *rend() { return F.rend(); }

  T operator[](size_t ind) { return F[ind]; }

  T getinv(int i) {
    assert(0 <= i && i <= _n);
    return FINV[i];
  }
  T nCr(int n, int k) {
    if (k < 0 || n < k)
      return (T)0;

    return F[n] * FINV[n - k] * FINV[k];
  }
  T nPr(int n, int k) {
    if (k < 0 || n < k)
      return (T)0;

    return F[n] * FINV[n - k];
  }
};
#line 35 "/home/hidehic0/src/github.com/hidehic0/library_cpp/all.h"

#line 3 "/home/hidehic0/src/github.com/hidehic0/library_cpp/data-structure/removable_priority_queue.hpp"

template <typename T, typename Compare = std::less<T>>
struct RemovablePriorityQueue {
  std::priority_queue<T, std::vector<T>, Compare> PQ, RPQ;

  void m_remove() {
    if (PQ.empty())
      return;

    while (true) {
      if (PQ.empty() || RPQ.empty())
        return;

      if (PQ.top() == RPQ.top())
        PQ.pop(), RPQ.pop();
      else
        return;
    }
  }

  void push(T v) { PQ.push(v); }

  void remove(T v) { RPQ.push(v); }

  bool empty() {
    m_remove();

    return PQ.empty();
  }

  T top() {
    assert(!empty());
    return PQ.top();
  }

  void pop() {
    assert(!empty());
    PQ.pop();
  }
};
#line 5 "main.cpp"

using namespace std;
using namespace atcoder;

ll dp[1771561]{0};

int main() {
  ll N;
  in(N);

  rep(_, N) {
    string S;
    ll V;
    in(S, V);

    ll cur = 0;
    rep(i, 6) cur *= 11, cur += int(S[i] - '0') + 1;

    dp[cur] += V;
  }

  vi pt(7);
  pt[0] = 1;
  rep(i, 6) pt[i + 1] = pt[i] * 11;

  rep(i, 1771561) {
    bool flag = false;
    rep(k, 6) {
      if ((i / pt[k]) % 11 == 0)
        flag = true;
    }

    if (flag)
      continue;

    rep(bit, 1, 1 << 6) {
      ll ni = 0;

      rep(k, 6) {
        if ((bit >> k) & 1)
          ni += (i / pt[k] % 11 - 1) * pt[k];
        else
          ni += (i / pt[k] % 11) * pt[k];
      }

      dp[i] += dp[ni] * ll(popcount(uint32_t(bit)) & 1 ? 1 : -1);
    }
  }

  ll Q;
  in(Q);

  while (Q--) {
    string x, y;
    in(x, y);

    bool flag = false;

    rep(i, 6) {
      if (x[i] > y[i]) {
        flag = true;
        break;
      }
    }

    if (flag) {
      out(0);
      continue;
    }

    vi X, Y;

    rep(i, 6) X.emplace_back(x[i] - '0'), Y.emplace_back(y[i] - '0' + 1);

    ll res = 0;

    rep(bit, 1 << 6) {
      ll cur = 0;

      rep(i, 6) {
        cur *= 11;
        if ((bit >> i) & 1)
          cur += X[i];
        else
          cur += Y[i];
      }

      res += ll(popcount(uint32_t(bit)) & 1 ? -1 : 1) * dp[cur];
    }

    out(res);
  }
}

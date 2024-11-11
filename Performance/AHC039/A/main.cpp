#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
using namespace std;

// 型テンプレ
using ll = long long;
using ull = unsigned long long;

// マクロ

#define rep(i, n) for (ll i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()

void printbase() { cout << '\n'; }

template <typename T> void printbase(const T &t) { cout << t << '\n'; }

template <typename T> void printbase(const std::vector<T> &vec) {
  for (const auto &v : vec) {
    cout << v << ' ';
  }
  cout << '\n';
}

template <typename Head, typename... Tail>
void printbase(const Head &head, const Tail &...tail) {
  cout << head << ' ';
  printbase(tail...);
}

#define print(...)                                                             \
  {                                                                            \
    printbase(__VA_ARGS__);                                                    \
    return 0;                                                                  \
  }

const ll INF = pow(10, 18);
const string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string lowerlist = "abcdefghijklmnopqrstuvwxyz";
ll rnd() {
  static ll tx = 123456789, ty = 362436069, tz = 521288629, tw = 88675123;
  ll tt = (tx ^ (tx << 11));
  tx = ty;
  ty = tz;
  tz = tw;
  return (tw = (tw ^ (tw >> 19)) ^ (tt ^ (tt >> 8)));
}

ll RandInt(ll a, ll b) { return a + rnd() % (b - a + 1); }

ll N;
ll GetScore(pair<ll, ll> a, pair<ll, ll> b, pair<ll, ll> c, pair<ll, ll> d,
            vector<pair<ll, ll>> m, vector<pair<ll, ll>> s) {
  ll x = 0;
  ll y = 0;

  rep(i, N) {
    if (a.first <= m[i].first && b.first >= m[i].first &&
        a.second <= m[i].second && c.second >= m[i].second) {
      x += 1;
    }
  }
  rep(i, N) {
    if (a.first <= s[i].first && b.first >= s[i].first &&
        a.second <= s[i].second && c.second >= s[i].second) {
      y += 1;
    }
  }
  ll zero = 0;
  ll tmp = x - y + 1;
  ll result = max(zero, tmp);

  return result;
}

double RD() { return 1.0 * rand() / RAND_MAX; }

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin >> N;
  vector<pair<ll, ll>> M(N);
  vector<pair<ll, ll>> S(N);
  ll xma = 0;
  ll xmi = INF;
  ll yma = 0;
  ll ymi = INF;

  rep(i, N) {
    cin >> M[i].first >> M[i].second;
    xmi = min(xmi, M[i].first);
    xma = max(xma, M[i].first);
    ymi = min(xmi, M[i].second);
    yma = max(xma, M[i].second);
  }
  rep(i, N) { cin >> S[i].first >> S[i].second; }

  pair<ll, ll> a;
  a.first = 0;
  a.second = 0;
  pair<ll, ll> b;
  b.first = pow(10, 5);
  b.second = 0;
  pair<ll, ll> c;
  c.first = 0;
  c.second = pow(10, 5);
  pair<ll, ll> d;
  d.first = pow(10, 5);
  d.second = pow(10, 5);
  ll score = 0;
  rep(i, 31000) {
    // 山登り法
    ll t = rnd() % 4;

    if (t == 0) {
      ll bx = b.first;
      ll r = RandInt(a.first + 1, xma);
      b.first = r;
      d.first = r;
      ll ts = GetScore(a, b, c, d, M, S);
      double T = 40.00 - 38.00 * (i + 1) / 30000.0;
      double Probability = exp(min(0.0, (ts - score) / T));
      if (RD() < Probability) {
        score = ts;
        cout << 4 << endl;
        cout << a.first << " " << a.second << endl;
        cout << c.first << " " << c.second << endl;
        cout << d.first << " " << d.second << endl;
        cout << b.first << " " << b.second << endl;
      } else {
        b.first = bx;
        d.first = bx;
      }
    } else if (t == 1) {

      ll by = a.second;
      ll r = RandInt(ymi, c.second - 1);
      b.second = r;
      a.second = r;
      ll ts = GetScore(a, b, c, d, M, S);
      double T = 40.00 - 38.00 * (i + 1) / 30000.0;
      double Probability = exp(min(0.0, (ts - score) / T));
      if (RD() < Probability) {
        score = ts;
        cout << 4 << endl;
        cout << a.first << " " << a.second << endl;
        cout << c.first << " " << c.second << endl;
        cout << d.first << " " << d.second << endl;
        cout << b.first << " " << b.second << endl;
      } else {
        a.second = by;
        b.second = by;
      }
    } else if (t == 2) {

      ll bx = a.first;
      ll r = RandInt(xmi, b.first - 1);
      a.first = r;
      c.first = r;
      ll ts = GetScore(a, b, c, d, M, S);
      double T = 40.00 - 38.00 * (i + 1) / 30000.0;
      double Probability = exp(min(0.0, (ts - score) / T));
      if (RD() < Probability) {
        score = ts;
        cout << 4 << endl;
        cout << a.first << " " << a.second << endl;
        cout << c.first << " " << c.second << endl;
        cout << d.first << " " << d.second << endl;
        cout << b.first << " " << b.second << endl;
      } else {
        a.first = bx;
        c.first = bx;
      }
    } else if (t == 3) {

      ll by = c.second;
      ll r = RandInt(b.second + 1, yma);
      c.second = r;
      d.second = r;
      ll ts = GetScore(a, b, c, d, M, S);
      double T = 40.00 - 38.00 * (i + 1) / 30000.0;
      double Probability = exp(min(0.0, (ts - score) / T));
      if (RD() < Probability) {
        score = ts;
        cout << 4 << endl;
        cout << a.first << " " << a.second << endl;
        cout << c.first << " " << c.second << endl;
        cout << d.first << " " << d.second << endl;
        cout << b.first << " " << b.second << endl;
      } else {
        c.second = by;
        d.second = by;
      }
    }
  }

  /*cout << 0 << " " << 0 << endl;*/
  /*ll b = RandInt(5, pow(10, 5));*/
  /*ll c = RandInt(5, pow(10, 5));*/
  /*cout << b << " " << 0 << endl;*/
  /*cout << b << " " << c << endl;*/
  /*cout << 0 << " " << c << endl;*/
  cout << 4 << endl;
  cout << a.first << " " << a.second << endl;
  cout << c.first << " " << c.second << endl;
  cout << d.first << " " << d.second << endl;
  cout << b.first << " " << b.second << endl;
}

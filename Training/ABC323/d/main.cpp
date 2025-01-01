#include <bits/stdc++.h>
#pragma GCC target("avx2")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
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

ll N;

int main() {
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  cin >> N;
  map<ll, ll> D;
  map<long long, long long>::iterator itr;

  rep(_, N) {
    ll S, C;
    cin >> S >> C;
    D[S] = 0;
    D[S] += C;
  }
  ll ans = 0;
  itr = D.begin();
  while (itr != D.end()) {
    ll x = (*itr).first, y = (*itr).second;

    if (y > 1) {
      D[x * 2] += (y / 2);
    }
    if (y & 1) {
      ans++;
    }
    itr++;
  }

  cout << ans << endl;
}

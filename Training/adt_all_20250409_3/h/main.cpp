#include <bits/stdc++.h>
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

ll N, K;
int main() {
  cin >> N >> K;
  vector<ll> A(N), ans(pow(10, 6) + 100, 1), D(pow(10, 6) + 100, 0);

  rep(i, N) {
    cin >> A[i];
    D[A[i]]++;
  }

  rep(i, pow(10, 6) + 100) {
    if (i == 0) {
      continue;
    }

    ll k = i, cnt = 0;

    while (k <= pow(10, 6)) {
      cnt += D[k];
      k += i;
    }

    if (cnt >= K) {
      ll k = i;

      while (k <= pow(10, 6)) {
        ans[k] = i;
        k += i;
      }
    }
  }

  rep(i, N) { cout << ans[A[i]] << "\n"; }
}

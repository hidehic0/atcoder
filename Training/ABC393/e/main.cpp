#include <bits/stdc++.h>
using namespace std;

// 型テンプレ
using ll = long long;
using ull = unsigned long long;

// マクロ

#define rep(i, n) for (ll i = 0; i < (int)(n); i++)
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
  ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  cin >> N >> K;

  vector<ll> A(N);
  rep(i, N) { cin >> A[i]; }

  ll MAX = *max_element(all(A));
  vector<ll> ans(MAX + 1);
  vector<ll> D(MAX + 1);

  rep(i, N) { D[A[i]]++; }

  for (ll i = 1; i <= MAX; i++) {
    ll cnt = 0;
    for (ll k = i; k <= MAX; k += i) {
      cnt += D[k];
    }

    if (cnt < K) {
      continue;
    }

    for (ll k = i; k <= MAX; k += i) {
      ans[k] = max(ans[k], i);
    }
  }

  rep(i, N) { cout << ans[A[i]] << "\n"; }
}

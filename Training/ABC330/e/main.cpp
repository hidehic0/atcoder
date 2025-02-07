#include <bits/stdc++.h>
#include <map>
#include <set>
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
ll N, Q;
map<ll, ll> D;
set<ll> L;

int main() {
  cin >> N >> Q;
  vector<ll> A(N);

  rep(i, N) {
    cin >> A[i];
    D[A[i]]++;
  }

  for (ll i = 0; i <= N + 100; ++i) {
    if (D[i] == 0) {
      L.insert(i);
    }
  }
  while (Q--) {
    ll i, x;
    cin >> i >> x;
    i--;

    D[A[i]]--;

    if (D[A[i]] == 0) {
      L.insert(A[i]);
    }

    A[i] = x;
    D[x]++;

    if (D[x] == 1) {
      L.erase(x);
    }

    cout << *L.begin() << "\n";
  }
}

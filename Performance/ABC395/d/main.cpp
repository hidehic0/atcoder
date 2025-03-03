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

ll N, Q;

int main() {
  cin >> N >> Q;
  vector<ll> hato(N);
  vector<set<ll>> subako(N, set<ll>());

  rep(i, N) {
    hato[i] = i;
    subako[i].insert(i);
  }

  while (Q--) {
    ll t;
    cin >> t;

    if (t == 1) {
      ll a, b;
      cin >> a >> b;
      a--;
      b--;

      subako[b].insert(a);
      subako[hato[a]].erase(a);
      hato[a] = b;
    } else if (t == 2) {
      ll a, b;
      cin >> a >> b;
      a--;
      b--;

      for (auto x : subako[hato[a]]) {
        hato[x] = b;
      }

      for (auto x : subako[b]) {
        hato[x] = a;
      }

      swap(subako[a], subako[b]);
    } else {
      ll a;
      cin >> a;
      a--;
      cout << hato[a] + 1 << '\n';
    }
  }
}

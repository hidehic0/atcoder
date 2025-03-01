#include <bits/stdc++.h>
#include <string>
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

ll N, M, a, b;
ll ans = 0;
string S;

int main() {
  cin >> N >> M >> S;
  vector<vector<ll>> graph(N, vector<ll>{});

  rep(i, M) {
    cin >> a >> b;
    a--;
    b--;
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vector<bool> used(N, false);
  map<ll, string> D = {{0, "o"}, {1, "x"}};
  ll mod = 998244353;
  ll hatena_count = 0;
  string hatena = "?";

  rep(i, N) {
    if (S[i] == hatena) {
      hatena_count++;
    }
  }

  auto dfs = [](ll cur, ll turn) {
    if (turn == 2) {
      ans++;
      return;
    }
  };
}

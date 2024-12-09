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

ll N, M;
vector<vector<ll>> ans;

void dfs(vector<ll> l) {
  if (l.size() == N) {
    ans.push_back(l);
    return;
  }
  ll i = l[l.size() - 1] + 10;
  ll tmp = (10 * (N - l.size()));
  while (i < M - tmp) {
    l.push_back(i);
    dfs(l);
    l.pop_back();
    i++;
  }
}

int main() {
  cin >> N >> M;
  for (ll i = 1; i <= M - (10 * (N - 1)); i++) {
    dfs({i});
  }

  cout << ans.size() << endl;
  rep(i, ans.size()) {
    rep(k, N) { cout << ans[i][k] << " "; }
    cout << endl;
  }
}

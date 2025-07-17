#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

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

const ll INF = (ll)1 << 63;
const string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string lowerlist = "abcdefghijklmnopqrstuvwxyz";

int main() {
  ll N, M;
  cin >> N >> M;
  vector<ll> deg(N);
  dsu UF(N);

  rep(_, M) {
    ll a, b;
    string c, d;
    cin >> a >> c >> b >> d;
    a--;
    b--;
    deg[a]++;
    deg[b]++;

    UF.merge(a, b);
  }

  set<ll> L;

  rep(i, N) { L.emplace(UF.leader(i)); }

  map<ll, bool> D;

  for (auto l : L) {
    D[l] = true;
  }

  rep(i, N) {
    if (deg[i] != 2) {
      D[UF.leader(i)] = false;
    }
  }

  ll ans = 0;

  for (auto l : L) {
    if (D[l]) {
      ans++;
    }
  }

  cout << ans << " " << L.size() - ans << "\n";
}

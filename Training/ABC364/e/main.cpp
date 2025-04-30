#include <bits/stdc++.h>
using namespace std;

// 型テンプレ

// マクロ

#define rep(i, n) for (int i = 0; i < n; i++)
#define aint(a) (a).begin(), (a).end()

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

const int INF = 1e9;
const string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string lowerlist = "abcdefghijklmnopqrstuvwxyz";

int main() {
  int N, X, Y;
  cin >> N >> X >> Y;
  vector<int> a(N), b(N);

  for (int i = 0; i < N; i++) {
    cin >> a[i] >> b[i];
  }

  vector dp(N + 1, vector(N + 1, vector<int>(X + 1, 1e9)));

  dp[0][0][0] = 0;

  rep(i, N) {
    int A, B;
    A = a[i];
    B = b[i];

    rep(k, N + 1) {
      rep(x, X + 1) {
        if (dp[i][k][x] == 1e9) {
          continue;
        }

        chmin(dp[i + 1][k][x], dp[i][k][x]);
        if (x + A <= X && k + 1 <= N) {
          chmin(dp[i + 1][k + 1][x + A], dp[i][k][x] + B);
        }
      }
    }
  }

  int ans = 0;

  rep(i, N + 1) {
    rep(k, N + 1) {
      rep(x, X + 1) {
        if (dp[i][k][x] <= Y) {
          chmax(ans, k);
        }
      }
    }
  }

  cout << min(ans + 1, N) << endl;
}

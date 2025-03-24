#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

// 型テンプレ
using ll = long long;
using ull = unsigned long long;

// マクロ

#define rep(i, n) for (ll i = 0; i < (int)(n); i++)
#define all(a) (a).begin(), (a).end()

void printbase() { cout << '\n'; }

template <typename T>
void printbase(const T &t)
{
    cout << t << '\n';
}

template <typename T>
void printbase(const std::vector<T> &vec)
{
    for (const auto &v : vec)
    {
        cout << v << ' ';
    }
    cout << '\n';
}

template <typename Head, typename... Tail>
void printbase(const Head &head, const Tail &...tail)
{
    cout << head << ' ';
    printbase(tail...);
}

#define print(...)              \
    {                           \
        printbase(__VA_ARGS__); \
        return 0;               \
    }

const ll INF = pow(10, 18);
const string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string lowerlist = "abcdefghijklmnopqrstuvwxyz";

ll N,R,C;
string S;

int main()
{
  cin >> N>>R>>C>>S;
  string ans; 
  map<ll, set<int>> X,Y;
  X[0].insert(0);
  Y[0].insert(0);

  rep(i, N) { 
    char cs = S[i];
    string s = string(1,cs);

    if (s=="N") {
      for (const auto& [y, yset] : Y) {
        for (auto x : yset) {
          Y[y].insert(x-1);
          Y[y].erase(x);

          X[x-1].insert(y);
          X[x].erase(y);
        }
      }
    } else if (s == "W") {
      for (const auto& [y, yset] : Y) {
        vector<ll> ys;
        for (auto x: yset)  {
          ys.push_back(x);
        }

        reverse(all(ys));

        for (auto x :  ys) {
          Y[y].insert(x+1);
          Y[y].erase(x);

          X[x+1].insert(y);
          X[x].erase(y);
        }
      }
    }else if (s == "W") {
    
      for (const auto& [x, xset] : X) {
        for (auto y :xset) {
          X[x+1].insert(y);
          X[x].erase(y);

          Y[y].insert(x+1);
          Y[y].erase(x);
        }
      }
    }
  }
  cout << ans << "\n";
}

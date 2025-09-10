#include <atcoder/fenwicktree>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

using ll = long long;
using pii = pair<int, int>;

// 座標圧縮
template <class T> auto compress_1d(const vector<T> &points) {
  vector<T> vals(points.begin(), points.end());
  sort(vals.begin(), vals.end());
  vals.erase(unique(vals.begin(), vals.end()), vals.end());

  unordered_map<T, int> d;
  for (int i = 0; i < (int)vals.size(); i++) {
    d[vals[i]] = i;
  }
  return d;
}

// 二分探索
template <class F>
int binary_search(F fn, int right, int left = -1, bool return_left = true) {
  while (right - left > 1) {
    int mid = (left + right) / 2;
    if (fn(mid))
      left = mid;
    else
      right = mid;
  }
  return return_left ? left : right;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int N;
  cin >> N;
  vector<pii> L(N);
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    L[i] = {a, b};
  }

  sort(L.begin(), L.end());
  vector<int> Y;
  for (auto &p : L)
    Y.push_back(p.second);
  sort(Y.begin(), Y.end());

  auto y_map = compress_1d(Y);

  auto f = [&](int k) -> bool {
    fenwick_tree<int> ft(N);
    int cur = 0;
    for (int i = 1; i < N; i++) {
      while (cur < i && L[i].first - L[cur].first >= k) {
        ft.add(y_map[L[cur].second], 1);
        cur++;
      }

      int a = -1, b = -1;
      int bis_a = lower_bound(Y.begin(), Y.end(), L[i].second + k) - Y.begin();
      if (bis_a < N) {
        a = ft.sum(y_map[Y[bis_a]], N);
      }

      int bis_b =
          (int)(upper_bound(Y.begin(), Y.end(), L[i].second - k) - Y.begin()) -
          1;
      if (bis_b >= 0 && abs(L[i].second - Y[bis_b]) >= k) {
        b = ft.sum(0, y_map[Y[bis_b]] + 1);
      }

      if ((a >= 1) || (b >= 1))
        return true;
    }
    return false;
  };

  int ans = binary_search(
      f, min(Y.back() - Y.front(), L.back().first - L.front().first) + 1, 0);
  cout << ans << "\n";
}

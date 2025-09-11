#include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

template <typename T> map<T, T> compress(vector<T> L) {
  set<T> st;
  map<T, T> res;

  rep(i, L.size()) st.emplace(L[i]);

  auto it = st.begin();
  T i = 1;

  while (it != st.end()) {
    T tmp = *it;
    res.emplace(tmp, i);
    i++;
    it++;
  }

  return res;
}

ll op(ll a, ll b) { return max(a, b); }
ll e() { return 0; }

int main() {
  ll T;
  cin >> T;
  while (T--) {
    ll N;
    cin >> N;
    vi A(N);
    rep(i, N) cin >> A[i];

    auto D = compress(A);

    segtree<ll, op, e> seg_fe(N + 1);
    segtree<ll, op, e> seg_fb(N + 1);
    vi prev;

    rrep(i, N) {
      prev.emplace_back(seg_fe.get(D[A[i]]));
      if (D[A[i]] == N) {
        seg_fe.set(D[A[i]], 1);
        continue;
      }

      seg_fe.set(D[A[i]], seg_fe.prod(D[A[i]] + 1, N + 1) + 1);
    }

    reverse(all(prev));

    ll lis_l = seg_fe.all_prod();
    vi ans;

    rep(i, N) {
      seg_fe.set(D[A[i]], prev[i]);
      ll l = seg_fb.prod(0, D[A[i]]) + 1 +
             (D[A[i]] == N ? 0 : seg_fe.prod(D[A[i]] + 1, N + 1));

      if (l == lis_l) {
        ans.emplace_back(i + 1);
      }

      seg_fb.set(D[A[i]], seg_fb.prod(0, D[A[i]]) + 1);
    }

    cout << ans.size() << "\n";

    rep(i, ans.size()) cout << ans[i] << (i + 1 == ans.size() ? "\n" : " ");
  }
}

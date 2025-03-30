// #include <atcoder/all>
#include <bits/stdc++.h>
using namespace std;
// using namespace atcoder;

#define OVERLOAD_REP(_1, _2, _3, _4, name, ...) name
#define REP1(i, n) for (auto i = decay_t<decltype(n)>{}; (i) < (n); ++(i))
#define REP2(i, l, r) for (auto i = (l); (i) < (r); ++(i))
#define REP3(i, l, r, d) for (auto i = (l); (i) < (r); i += (d))
#define rep(...) OVERLOAD_REP(__VA_ARGS__, REP3, REP2, REP1)(__VA_ARGS__)
#define rrep(i, r, l) for (int i = (r); i >= (l); --i)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define YesNo(b) ((b) ? "Yes" : "No")
#define YESNO(b) ((b) ? "YES" : "NO")
#define yesno(b) ((b) ? "yes" : "no")
#define chmax(a, b) a = max(a, b)
#define chmin(a, b) a = min(a, b)

// using mint = modint998244353;
using ull = unsigned long long;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vll = vector<ll>;
using vb = vector<bool>;
using vs = vector<string>;
using vc = vector<char>;
using vvi = vector<vi>;
using vvll = vector<vll>;
using vvb = vector<vb>;
using vvs = vector<vs>;
using vvc = vector<vc>;
using vvvi = vector<vvi>;
using vvvll = vector<vvll>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using vvpii = vector<vpii>;
using vvpll = vector<vpll>;

constexpr int dx[4] = {1, 0, -1, 0};
constexpr int dy[4] = {0, 1, 0, -1};
constexpr int INF = 1 << 30;
constexpr ll LINF = 1LL << 60;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;
    set<pll> A;
    rep(i, N) {
        int a;
        cin >> a;
        A.insert({a, i});
    }
    sort(all(A));
    int Q;
    cin >> Q;
    rep(i, Q) {
        ll b;
        cin >> b;
        // nearest_index
        auto it = lower_bound(all(A), pair(b, -1LL));
        if ((*it).first == b || it == A.begin()) {
            cout << (*it).second + 1 << endl;
        } else {
            ll d = abs((*it).first - b);
            it--;
            if (abs((*it).first - b) < d || ((abs((*it).first - b) == d) && (*it).second < next(it)->second)) {
                cout << (*it).second + 1 << endl;
            } else {
                it++;
                cout << (*it).second + 1 << endl;
            }
        }
        int idx = (*it).second;
        A.erase(it);
        A.insert({b, idx});
    }
}

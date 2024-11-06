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
    }

const ll INF = pow(10, 18);
const string upperlist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const string lowerlist = "abcdefghijklmnopqrstuvwxyz";
ll N, M, P;

int main()
{
    cin >> N >> M >> P;
    vector<ll> A(N), B(M);
    rep(i, N)
    {
        cin >> A[i];
    }

    rep(i, M)
    {
        cin >> B[i];
    }
    sort(all(B));
    for (ll i = 1; i < M; i++)
    {
        B[i] = B[i - 1] + B[i];
    }

    auto isOK = [&](ll ind, ll t)
    {
        if ((t * (ind + 1)) + B[ind] <= P * (ind + 1))
        {
            return false;
        }
        else
        {
            return true;
        }
    };

    ll ans = 0;
    rep(i, N)
    {
        ll ng = -1, ok = M;
        while (ok - ng > 1)
        {
            ll mid = (ok + ng) / 2;
            if (isOK(mid, A[i]))
            {
                ng = mid;
            }
            else
            {
                ok = mid;
            }
        }

        // 正しい結果の計算式にする
        ans += (A[i] * (ng + 1)) + B[ng] + ((M - ng) * P);
    }

    print(ans); // マクロのreturn 0を削除
}

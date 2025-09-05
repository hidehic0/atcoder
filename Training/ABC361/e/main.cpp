#pragma GCC TARGET("O3")

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// エラトステネスの篩
vector<int> eratosthenes(int n) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * 1LL * i <= n; i++) {
    if (is_prime[i]) {
      for (int j = i * 2; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  vector<int> primes;
  for (int i = 2; i <= n; i++) {
    if (is_prime[i])
      primes.push_back(i);
  }
  return primes;
}

// 複数数の素因数分解
vector<vector<pair<int, int>>> factorization_plural(int nmax) {
  vector<vector<pair<int, int>>> res(nmax + 1);
  vector<int> primes = eratosthenes((int)sqrt(nmax) + 20);

  for (int n = 1; n <= nmax; n++) {
    int tmp = n;
    for (int p : primes) {
      if ((ll)p * p > tmp)
        break;
      if (tmp % p == 0) {
        int cnt = 0;
        while (tmp % p == 0) {
          tmp /= p;
          cnt++;
        }
        res[n].push_back({p, cnt});
      }
    }
    if (tmp != 1) {
      res[n].push_back({tmp, 1});
    }
  }
  return res;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll N;
  cin >> N;

  ll ans = (ll)sqrtl(N);

  vector<int> L = eratosthenes(60);
  unordered_set<int> prime_set(L.begin(), L.end());

  int LIM = 1'000'001;
  auto FL = factorization_plural(LIM);

  for (int b = 3; b <= 61; b++) {
    if (!prime_set.count(b))
      continue;
    if ((1LL << b) > N)
      continue;

    ll i = 2;
    while (true) {
      __int128 pow = 1;
      for (int k = 0; k < b; k++) {
        pow *= i;
        if (pow > N)
          break;
      }
      if (pow > N)
        break;

      // 素因数分解を取り出し
      auto l = FL[i];
      vector<pair<int, int>> factors;
      for (auto [p, c] : l) {
        factors.push_back({p, c * b});
      }

      bool ok = false;
      for (int d = 2; d < b; d++) {
        bool flag = true;
        for (auto [p, c] : factors) {
          if (c % d != 0) {
            flag = false;
            break;
          }
        }
        if (flag) {
          ok = true;
          break;
        }
      }

      if (!ok)
        ans++;

      i++;
    }
  }

  cout << ans << "\n";
  return 0;
}

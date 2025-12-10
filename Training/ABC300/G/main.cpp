#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

int main() {
  vi primes = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31, 37, 41,
               43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};

  ll N, P;
  cin >> N >> P;
  vi L = {1}, T = {1};

  ll ind = 0;

  while (ind < primes.size() && primes[ind] <= P) {
    if (L.size() > 1e7)
      break;

    vi NL;

    for (ll i : L) {
      rep(k, 60) {
        if (pow(primes[ind], k) * i <= N) {
          NL.emplace_back(pow(primes[ind], k) * i);
        } else {
          break;
        }
      }
    }

    L = NL;
    ind++;
  }

  while (ind < primes.size() && primes[ind] <= P) {
    vi NT;

    for (ll i : T) {
      rep(k, 60) {
        if (pow(primes[ind], k) * i <= N) {
          NT.emplace_back(pow(primes[ind], k) * i);
        } else {
          break;
        }
      }
    }

    T = NT;
    ind++;
  }

  sort(all(L));
  sort(all(T));

  ind = L.size() - 1;
  ll ans = 0;

  for (ll i : T) {
    ll k = N / i;
    while (ind >= 0 && L[ind] > k)
      ind--;

    if (ind < 0)
      break;
    ans += ind + 1;
  }

  cout << ans << "\n";
}

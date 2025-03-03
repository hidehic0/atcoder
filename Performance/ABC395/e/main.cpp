
#include <iostream>
#include <limits>
#include <queue>
#include <vector>
using namespace std;

const long long INF = numeric_limits<int>::max();

int main() {
  long long N, M, X;
  cin >> N >> M >> X;

  vector<vector<long long>> A(N), B(N);

  for (long long i = 0; i < M; ++i) {
    long long u, v;
    cin >> u >> v;
    --u;
    --v;
    A[u].push_back(v);
    B[v].push_back(u);
  }

  vector<vector<long long>> G[2] = {A, B};
  vector<vector<long long>> used(N, vector<long long>(2, INF));
  used[0][0] = 0;

  priority_queue<tuple<long long, long long, long long>,
                 vector<tuple<long long, long long, long long>>, greater<>>
      PQ;
  PQ.emplace(0, 0, 0);

  while (!PQ.empty()) {
    auto [cos, cur, mode] = PQ.top();
    PQ.pop();

    if (used[cur][mode] < cos)
      continue;

    if (used[cur][mode ^ 1] > cos + X) {
      used[cur][mode ^ 1] = cos + X;
      PQ.emplace(cos + X, cur, mode ^ 1);
    }

    for (long long nxt : G[mode][cur]) {
      if (used[nxt][mode] > cos + 1) {
        used[nxt][mode] = cos + 1;
        PQ.emplace(cos + 1, nxt, mode);
      }
    }
  }

  cout << min(used[N - 1][0], used[N - 1][1]) << endl;

  return 0;
}

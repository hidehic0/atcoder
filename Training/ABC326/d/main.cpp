#include <bits/stdc++.h>
using namespace std;

#include "templates/alias.hpp"
#include "templates/macro.hpp"

struct S {
  ll tp, ind;
  VC<VC<char>> cur;
};

int main() {
  ll N;
  string R, C;
  cin >> N >> R >> C;

  map<char, VC<char>> D;
  D['A'] = {'A', 'B', 'C'};
  D['B'] = {'B', 'A', 'C'};
  D['C'] = {'C', 'A', 'B'};

  stack<S> Q;

  Q.emplace(S{0, 0, VC<VC<char>>(N, VC<char>(N, '.'))});

  while (!Q.empty()) {
    S st = Q.top();
    Q.pop();

    // cout << st.tp dms st.ind << "\n";

    if (st.tp == 0 && st.ind == N) {

      Q.emplace(1, 0, st.cur);
      continue;
    }
    if (st.tp == 1 && st.ind == N) {
      cout << "Yes" << "\n";
      rep(i, N) {
        rep(k, N) { cout << st.cur[i][k]; }
        cout << "\n";
      }
      return 0;
    }

    if (st.tp == 0) {
      rep(a, N) {
        REP(b, a + 1, N) {
          REP(c, b + 1, N) {
            {
              S nxt = st;
              nxt.cur[st.ind][a] = D[R[st.ind]][0];
              nxt.cur[st.ind][b] = D[R[st.ind]][1];
              nxt.cur[st.ind][c] = D[R[st.ind]][2];
              nxt.ind++;
              Q.emplace(nxt);
            }

            {
              S nxt = st;
              nxt.cur[st.ind][a] = D[R[st.ind]][0];
              nxt.cur[st.ind][b] = D[R[st.ind]][2];
              nxt.cur[st.ind][c] = D[R[st.ind]][1];
              nxt.ind++;
              Q.emplace(nxt);
            }
          }
        }
      }
    } else {
      vb isok(N);

      S nxt = st;

      rep(i, st.ind + 1) {
        rep(k, N) {
          if (st.cur[k][i] != '-') {
            isok[k] = true;
          }
        }
      }

      rep(a, N) {
        if (!isok[a])
          continue;
        REP(b, a + 1, N) {
          if (!isok[b])
            continue;

          REP(c, b + 1, N) {
            if (!isok[c])
              continue;

            if (!((st.cur[a][st.ind] != D[C[st.ind]][0] &&
                   st.cur[a][st.ind] != '-') ||
                  (st.cur[b][st.ind] != D[C[st.ind]][1] &&
                   st.cur[b][st.ind] != '-') ||
                  (st.cur[c][st.ind] != D[C[st.ind]][2] &&
                   st.cur[c][st.ind] != '-'))) {
              nxt.cur[a][st.ind] = D[C[st.ind]][0];
              nxt.cur[b][st.ind] = D[C[st.ind]][1];
              nxt.cur[c][st.ind] = D[C[st.ind]][2];
              goto OK;
            }

            if (!((st.cur[a][st.ind] != D[C[st.ind]][0] &&
                   st.cur[a][st.ind] != '-') ||
                  (st.cur[b][st.ind] != D[C[st.ind]][2] &&
                   st.cur[b][st.ind] != '-') ||
                  (st.cur[c][st.ind] != D[C[st.ind]][1] &&
                   st.cur[c][st.ind] != '-'))) {
              nxt.cur[a][st.ind] = D[C[st.ind]][0];
              nxt.cur[b][st.ind] = D[C[st.ind]][2];
              nxt.cur[c][st.ind] = D[C[st.ind]][1];
              goto OK;
            }
          }
        }
      }

      continue;
    OK:
      nxt.ind++;
      Q.emplace(nxt);
    }
  }

  cout << "No" << "\n";
}

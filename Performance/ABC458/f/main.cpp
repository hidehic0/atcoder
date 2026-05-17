/**
 library: https://github.com/hidehic0/library_cpp
**/
#include "all.h"

using namespace std;
using namespace atcoder;

//  https://ei1333.github.io/library/string/aho-corasick.hpp
#line 1 "structure/trie/trie.hpp"
template <int char_size> struct TrieNode {
  int nxt[char_size];

  int exist;
  vector<int> accept;

  TrieNode() : exist(0) { memset(nxt, -1, sizeof(nxt)); }
};

template <int char_size, int margin> struct Trie {
  using Node = TrieNode<char_size>;

  vector<Node> nodes;
  int root;

  Trie() : root(0) { nodes.push_back(Node()); }

  void update_direct(int node, int id) { nodes[node].accept.push_back(id); }

  void update_child(int node, int child, int id) { ++nodes[node].exist; }

  void add(const string &str, int str_index, int node_index, int id) {
    if (str_index == str.size()) {
      update_direct(node_index, id);
    } else {
      const int c = str[str_index] - margin;
      if (nodes[node_index].nxt[c] == -1) {
        nodes[node_index].nxt[c] = (int)nodes.size();
        nodes.push_back(Node());
      }
      add(str, str_index + 1, nodes[node_index].nxt[c], id);
      update_child(node_index, nodes[node_index].nxt[c], id);
    }
  }

  void add(const string &str, int id) { add(str, 0, 0, id); }

  void add(const string &str) { add(str, nodes[0].exist); }

  void query(const string &str, const function<void(int)> &f, int str_index,
             int node_index) {
    for (auto &idx : nodes[node_index].accept)
      f(idx);
    if (str_index == str.size()) {
      return;
    } else {
      const int c = str[str_index] - margin;
      if (nodes[node_index].nxt[c] == -1)
        return;
      query(str, f, str_index + 1, nodes[node_index].nxt[c]);
    }
  }

  void query(const string &str, const function<void(int)> &f) {
    query(str, f, 0, 0);
  }

  int count() const { return (nodes[0].exist); }

  int size() const { return ((int)nodes.size()); }
};
#line 2 "string/aho-corasick.hpp"

template <int char_size, int margin>
struct AhoCorasick : Trie<char_size + 1, margin> {
  using Trie<char_size + 1, margin>::Trie;

  const int FAIL = char_size;
  vector<int> correct;

  void build(bool heavy = true) {
    correct.resize(this->size());
    for (int i = 0; i < this->size(); i++) {
      correct[i] = (int)this->nodes[i].accept.size();
    }
    queue<int> que;
    for (int i = 0; i <= char_size; i++) {
      if (~this->nodes[0].nxt[i]) {
        this->nodes[this->nodes[0].nxt[i]].nxt[FAIL] = 0;
        que.emplace(this->nodes[0].nxt[i]);
      } else {
        this->nodes[0].nxt[i] = 0;
      }
    }
    while (!que.empty()) {
      auto &now = this->nodes[que.front()];
      int fail = now.nxt[FAIL];
      correct[que.front()] += correct[fail];
      que.pop();
      for (int i = 0; i < char_size; i++) {
        if (~now.nxt[i]) {
          this->nodes[now.nxt[i]].nxt[FAIL] = this->nodes[fail].nxt[i];
          if (heavy) {
            auto &u = this->nodes[now.nxt[i]].accept;
            auto &v = this->nodes[this->nodes[fail].nxt[i]].accept;
            vector<int> accept;
            set_union(begin(u), end(u), begin(v), end(v),
                      back_inserter(accept));
            u = accept;
          }
          que.emplace(now.nxt[i]);
        } else {
          now.nxt[i] = this->nodes[fail].nxt[i];
        }
      }
    }
  }

  unordered_map<int, int> match(const string &str, int now = 0) {
    unordered_map<int, int> result, visit_cnt;
    for (auto &c : str) {
      now = this->nodes[now].nxt[c - margin];
      visit_cnt[now]++;
    }
    for (auto &[now, cnt] : visit_cnt) {
      for (auto &v : this->nodes[now].accept)
        result[v] += cnt;
    }
    return result;
  }

  pair<int64_t, int> move(const char &c, int now = 0) {
    now = this->nodes[now].nxt[c - margin];
    return {correct[now], now};
  }

  pair<int64_t, int> move(const string &str, int now = 0) {
    int64_t sum = 0;
    for (auto &c : str) {
      auto nxt = move(c, now);
      sum += nxt.first;
      now = nxt.second;
    }
    return {sum, now};
  }
};

using mint = atcoder::modint998244353;
using vm = vector<mint>;
using vvm = vector<vm>;
using vvvm = vector<vvm>;
using pmm = pair<mint, mint>;
ostream &operator<<(ostream &os, const mint &i) {
  os << i.val();
  return os;
}
#ifdef ONLINE_JUDGE
#else
namespace cpp_dump::_detail {
template <int m>
inline std::string
export_var(const atcoder::static_modint<m> &mint, const std::string &indent,
           std::size_t last_line_length, std::size_t current_depth,
           bool fail_on_newline, const export_command &command) {
  return export_var(mint.val(), indent, last_line_length, current_depth,
                    fail_on_newline, command);
}
template <int m>
inline std::string
export_var(const atcoder::dynamic_modint<m> &mint, const std::string &indent,
           std::size_t last_line_length, std::size_t current_depth,
           bool fail_on_newline, const export_command &command) {
  return export_var(mint.val(), indent, last_line_length, current_depth,
                    fail_on_newline, command);
}
} // namespace cpp_dump::_detail
#endif

vvm mat_mul(vvm a, vvm b) {
  vvm res(a.size(), vm(b[0].size(), 0));

  rep(i, a.size()) {
    rep(j, b[0].size()) {
      rep(k, b.size()) { res[i][j] += a[i][k] * b[k][j]; }
    }
  }

  return res;
}
vvm mat_pow(vvm a, ll n) {
  vvm res(a[0].size(), vm(a.size()));
  rep(i, a.size()) res[i][i] = 1;

  while (n > 0) {
    if (n & 1)
      res = mat_mul(res, a);
    a = mat_mul(a, a);
    n >>= 1;
  }

  return res;
}

int main() {
  ll N, K;
  in(N, K);
  VC<string> S(K);
  in(S);

  AhoCorasick<26, 'a'> aho;

  for (auto s : S)
    aho.add(s);

  aho.build();

  ll M = aho.nodes.size();

  vvm A(M, vm(M, 0));

  rep(cur, M) {
    rep(n, 26) {
      auto [m, nxt] = aho.move('a' + n, cur);

      if (!m)
        A[nxt][cur]++;
    }
  }

  A = mat_pow(A, N);
  vvm B(M, vm(1, 0));
  B[0][0]++;
  B = mat_mul(A, B);

  mint ans = 0;

  rep(i, M) ans += B[i][0];

  cout << ans.val() << "\n";
}

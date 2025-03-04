#include <iostream>
#include <queue>
#include <vector>

// グラフクラスの定義
class Graph {
public:
  int N;                               // 頂点数
  bool dire;                           // 有向グラフかどうか
  std::vector<std::vector<int>> grath; // 隣接リスト
  std::vector<int> in_deg;             // 入次数

  // コンストラクタ
  Graph(int N, bool dire = false) : N(N), dire(dire), grath(N), in_deg(N, 0) {}

  // 新しい辺を追加
  void new_side(int a, int b) {
    grath[a].push_back(b);
    if (dire) {
      in_deg[b]++;
    }
    if (!dire) {
      grath[b].push_back(a);
    }
  }

  // 標準入力から辺を追加
  void side_input() {
    int a, b;
    std::cin >> a >> b;
    a--;
    b--; // 0-indexedに変換
    new_side(a, b);
  }

  // M個の辺を入力
  void input(int M) {
    for (int i = 0; i < M; i++) {
      side_input();
    }
  }

  // 頂点aの隣接頂点を返す
  std::vector<int> &get(int a) { return grath[a]; }

  // グラフ全体の隣接リストを返す
  std::vector<std::vector<int>> &all() { return grath; }
};

int main() {
  // 入力: 頂点数Nと辺数M
  int N, M;
  std::cin >> N >> M;

  // 頂点ごとの値Aを入力
  std::vector<int> A(N);
  for (int i = 0; i < N; i++) {
    std::cin >> A[i];
  }

  // 有向グラフを作成し、M個の辺を入力
  Graph G(N, false);
  G.input(M);

  // 答えを格納する配列（初期値0）
  std::vector<int> ans(N, 0);
  ans[0] = 1; // 初期条件

  // ヒープを定義（最小ヒープとして動作）
  auto comp = [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.first > b.first; // -nscが小さい順（nscが大きい順）
  };
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>> PQ;
  PQ.push({-1, 0}); // 初期要素: (-変化回数, 頂点)

  // ヒープを使用した探索
  while (!PQ.empty()) {
    auto [neg_sc, cur] = PQ.top(); // ヒープから取り出し
    PQ.pop();
    int sc = -neg_sc; // スコアを正に戻す

    if (sc < ans[cur]) { // 現在のスコアが記録より小さい場合はスキップ
      continue;
    }

    // 隣接頂点を探索
    for (int nxt : G.get(cur)) {
      if (A[cur] > A[nxt]) { // 条件を満たさない場合はスキップ
        continue;
      }
      int nsc = sc + (A[cur] < A[nxt]); // 新しいスコアを計算

      if (nsc > ans[nxt]) { // スコアが更新される場合
        ans[nxt] = nsc;
        PQ.push({-nsc, nxt}); // ヒープに追加
      }
    }
  }

  // 結果出力
  std::cout << ans[N - 1] << std::endl;

  return 0;
}

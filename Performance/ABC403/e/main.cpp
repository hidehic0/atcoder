/* Original Python Code:
r"""
 ______________________
< it's hidehico's code >
 ----------------------
   \
    \
        .--.
       |o_o |
       |:_/ |
      //   \ \
     (|     | )
    /'\_   _/`\
    \___)=(___/
"""

# ライブラリと関数と便利変数
# ライブラリ
import bisect
import copy
import heapq
import math
import sys
from collections import Counter, defaultdict, deque
from itertools import accumulate, combinations, permutations
from math import gcd, lcm, pi
from operator import itemgetter
from typing import Any, List, Tuple

# from atcoder.segtree import SegTree
# from atcoder.lazysegtree import LazySegTree
# from atcoder.dsu import DSU

# cortedcontainersは使うときだけ wandbox非対応なので
# from sortedcontainers import SortedDict, SortedSet, SortedList

# import pypyjit
# pypyjit.set_param("max_unroll_recursion=-1")

sys.setrecursionlimit(5 * 10**5)


def s() -> str:
    """
    一行に一つのstringをinput
    """
    return input()


def sl() -> List[str]:
    """
    一行に複数のstringをinput
    """
    return s().split()


def ii() -> int:
    """
    一つのint
    """
    return int(s())


def il(add_num: int = 0) -> List[int]:
    """
    一行に複数のint
    """
    return list(map(lambda i: int(i) + add_num, sl()))


def li(n: int, func, *args) -> List[List[Any]]:
    """
    複数行の入力をサポート
    """
    return [func(*args) for _ in [0] * n]


# Trie木
class Trie:
    class Data:
        def __init__(self, value, ind):
            self.count = 1
            self.value = value
            self.childs = {}
            self.ind = ind

    def __init__(self):
        self.data = [self.Data("ab", 0)]  # 初期値はabにして被らないようにする

    def add(self, value: str) -> int:
        cur = 0
        result = 0

        # 再帰的に探索する
        for t in value:
            childs = self.data[cur].childs  # 参照渡しで

            if t in childs:
                self.data[childs[t]].count += 1
            else:
                nd = self.Data(t, len(self.data))
                childs[t] = len(self.data)
                self.data.append(nd)

            result += self.data[childs[t]].count - 1
            cur = childs[t]

        return result

    def remove(self, value):
        cur = 0
        cnt = 0

        for t in value:
            childs = self.data[cur].childs
            if t not in childs:
                return 0

            cnt = self.data[childs[t]].count
            cur = childs[t]

        cur = 0

        for t in value:
            childs = self.data[cur].childs
            self.data[childs[t]].count -= cnt
            cur = childs[t]

        return cnt

    def lcp_max(self, value: str) -> int:
        cur = 0
        result = 0

        for t in value:
            childs = self.data[cur].childs

            if t not in childs:
                break

            if self.data[childs[t]].count == 1:
                break

            cur = childs[t]
            result += 1

        return result

    def lcp_sum(self, value: str) -> int:
        cur = 0
        result = 0

        for t in value:
            childs = self.data[cur].childs

            if t not in childs:
                break

            if self.data[childs[t]].count == 1:
                break

            cur = childs[t]
            result += self.data[childs[t]].count - 1

        return result


# コード
Q = ii()
X = set()
Y = Trie()

ans = 0

while Q:
    T, S = sl()
    T = int(T)

    if T == 1:
        ans -= Y.remove(S)
        X.add(S)
    else:
        f = True
        cur = ""

        for t in S:
            cur += t

            if cur in X:
                f = False

        ans += f
        Y.add(S)

    print(ans)

    Q -= 1
*/

#include <bits/stdc++.h>

using namespace std;

// Trie implementation
class Trie {
public:
    class Data {
    public:
        int count;
        string value;
        map<char, int> childs;
        int ind;

        Data(string val, int idx) : count(1), value(val), ind(idx) {}
    };

    vector<Data> data;

    Trie() {
        data.emplace_back("ab", 0); // Initialize with "ab" to avoid conflicts
    }

    int add(const string& value) {
        int cur = 0;
        int result = 0;

        for (char t : value) {
            auto& childs = data[cur].childs;

            if (childs.find(t) != childs.end()) {
                data[childs[t]].count += 1;
            } else {
                data.emplace_back(string(1, t), data.size());
                childs[t] = data.size() - 1;
            }

            result += data[childs[t]].count - 1;
            cur = childs[t];
        }

        return result;
    }

    int remove(const string& value) {
        int cur = 0;
        int cnt = 0;

        // First pass: find count
        for (char t : value) {
            auto& childs = data[cur].childs;
            if (childs.find(t) == childs.end()) {
                return 0;
            }
            cnt = data[childs[t]].count;
            cur = childs[t];
        }

        // Second pass: reduce counts
        cur = 0;
        for (char t : value) {
            auto& childs = data[cur].childs;
            data[childs[ t]].count -= cnt;
            cur = childs[t];
        }

        return cnt;
    }

    int lcp_max(const string& value) {
        int cur = 0;
        int result = 0;

        for (char t : value) {
            auto& childs = data[cur].childs;

            if (childs.find(t) == childs.end()) {
                break;
            }

            if (data[childs[t]].count == 1) {
                break;
            }

            cur = childs[t];
            result += 1;
        }

        return result;
    }

    int lcp_sum(const string& value) {
        int cur = 0;
        int result = 0;

        for (char t : value) {
            auto& childs = data[cur].childs;

            if (childs.find(t) == childs.end()) {
                break;
            }

            if (data[childs[t]].count == 1) {
                break;
            }

            cur = childs[t];
            result += data[childs[t]].count - 1;
        }

        return result;
    }
};

// Input functions
string s() {
    string input;
    getline(cin, input);
    return input;
}

pair<int, string> sl() {
    string line = s();
    size_t pos = line.find(' ');
    int t = stoi(line.substr(0, pos));
    string s = line.substr(pos + 1);
    return {t, s};
}

int ii() {
    return stoi(s());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int Q = ii();
    set<string> X;
    Trie Y;
    long long ans = 0;

    while (Q--) {
        auto [T, S] = sl();

        if (T == 1) {
            ans -= Y.remove(S);
            X.insert(S);
        } else {
            bool f = true;
            string cur = "";

            for (char t : S) {
                cur += t;
                if (X.find(cur) != X.end()) {
                    f = false;
                }
            }

            ans += f;
            Y.add(S);
        }

        cout << ans << '\n';
    }

    return 0;
}

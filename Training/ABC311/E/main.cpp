#include <iostream>
#include <vector>
#include <functional>

using namespace std;

// 2D array creation function
template<typename T>
vector<vector<T>> create_array2(int a, int b, T default_value = 0) {
    return vector<vector<T>>(a, vector<T>(b, default_value));
}

// Binary search template
int binary_search(function<bool(int)> fn, int right = 0, int left = -1, bool return_left = true) {
    while (right - left > 1) {
        int mid = (left + right) / 2;
        
        if (fn(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return return_left ? left : right;
}

// Main program
int main() {
    // Input
    int H, W, N;
    cin >> H >> W >> N;
    
    // Initialize 2D array
    vector<vector<long long>> L = create_array2(H + 1, W + 1, 0LL);
    
    // Process N points
    for (int _ = 0; _ < N; _++) {
        int a, b;
        cin >> a >> b;
        L[a][b] += 1;
    }
    
    // Calculate prefix sums (horizontal)
    for (int i = 0; i <= H; i++) {
        for (int k = 1; k <= W; k++) {
            L[i][k] += L[i][k - 1];
        }
    }
    
    // Calculate prefix sums (vertical)
    for (int k = 0; k <= W; k++) {
        for (int i = 1; i <= H; i++) {
            L[i][k] += L[i - 1][k];
        }
    }
    
    // Calculate answer
    long long ans = 0;
    
    for (int i = 0; i < H; i++) {
        for (int k = 0; k < W; k++) {
            // Lambda function for binary search
            auto c = [&](int mid) -> bool {
                int u = i + mid;
                int v = k + mid;
                return (L[u][v] - L[i][v] - L[u][k] + L[i][k]) == 0;
            };
            
            ans += binary_search(c, min(H - i, W - k) + 1, 0);
        }
    }
    
    cout << ans << endl;
    
    return 0;
}

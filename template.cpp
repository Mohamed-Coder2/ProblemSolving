#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

// Constants
int MOD = 1e9 + 7;
const int N = 1e7;

// Global arrays
int fact[N + 1];    // Factorial
int divisors[N];    // Divisors e.g divisors[6] = 4 (1,2,3,6), divisors[7] = 2 (1,7)
int spf[N];         // Smallest Prime Factor
int prefix[N];      // Prefix Sum
vector<int> adj[N]; // Adjacency list for graph
bool visited[N];
bool is_prime[N + 1]; // All Primes from 1 to N
vector<int> prime_prefix(N, 0);
int change_making_dp[N] = {0}; // Unique ways to generate change for N

// Basic math operations
int add(int a, int b) {
    a += b;
    if (a >= MOD) a -= MOD;
    return a;
}

int sub(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

int mul(int a, int b) {
    return 1LL * a * b % MOD;
}

int binary_exp(int x, int p) {
    int ret = 1;
    while (p) {
        if (p % 2 != 0)
            ret = mul(ret, x);
        x = mul(x, x);
        p /= 2;
    }
    return ret;
}

int modInverse(int x) {
    return binary_exp(x, MOD - 2);
}

int GCD(int a, int b) {
    if (b == 0) return a;
    return GCD(b, a % b);
}

int LCM(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a * b) / GCD(a, b);
}

// Factorial and combinatorics
void buildF() {
    fact[0] = 1;
    for (int i = 1; i <= N; i++) {
        fact[i] = mul(fact[i - 1], i);
    }
}

// Calculate the number of combinations of n items taken r at a time
// order doesn't matter
int nCr(int n, int r) {
    return mul(fact[n], modInverse(mul(fact[r], fact[n - r])));
}

// Calculate the number of permutations of n items taken r at a time
// order does matter
int nPr(int n, int r) {
    return mul(fact[n], modInverse(fact[n - r]));
}

// Calculate the Primes
void sieve() {
    fill(is_prime, is_prime + N, true);
    is_prime[0] = is_prime[1] = false;
    for (int i = 2; i <= N; ++i) {
        if (is_prime[i]) {
            for (int j = i + i; j <= N; j += i) {
                is_prime[j] = false;
            }
        }
    }
}

void compute_prefix() {
    prime_prefix[0] = 0;
    for (int i = 1; i < N; i++) {
        prime_prefix[i] = prime_prefix[i - 1] + (is_prime[i] ? 1 : 0);
    }
}

void precomputeSPF() {
    for (int i = 0; i < N; ++i)
        spf[i] = i;

    for (int i = 2; i * i < N; ++i) {
        if (spf[i] == i) {
            for (int j = i * i; j < N; j += i) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
}

vector<pair<int, int>> primeFactorization(int x) {
    vector<pair<int, int>> factors;
    while (x > 1) {
        int prime = spf[x];
        int count = 0;
        while (spf[x] == prime) {
            x /= prime;
            count++;
        }
        factors.emplace_back(prime, count);
    }
    return factors;
}

// Divisors functions
void buildD() {
    for (int i = 1; i < N; ++i) {
        for (int j = i; j < N; j += i) {
            divisors[j]++;
        }
    }
}

// Returns divisors of x in sorted order
vector<int> divisorsOfX(int x) {
    vector<int> res;
    int i;
    for (i = 1; i * i < x; i++) {
        if (x % i == 0) {
            res.push_back(i);
            res.push_back(x / i);
        }
    }
    if (i * i == x) res.push_back(i);
    sort(res.begin(), res.end());
    return res;
}

// Prefix sum functions
void buildPrefixSum(const vector<int> &arr) {
    prefix[0] = 0;
    for (int i = 1; i <= arr.size(); ++i) {
        prefix[i] = prefix[i - 1] + arr[i - 1];
    }
}

int rangeSum(int l, int r) {
    return prefix[r] - prefix[l - 1];
}

// Search functions
// Lower Bound: first index ≥ target
int lower_bound_idx(const vector<int>& a, int target) {
    return lower_bound(a.begin(), a.end(), target) - a.begin();
}

// Upper Bound: first index > target
int upper_bound_idx(const vector<int>& a, int target) {
    return upper_bound(a.begin(), a.end(), target) - a.begin();
}

int binarySearch(const vector<int>& arr, int target) {
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

// Graph functions
void dfs(int node) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor])
            dfs(neighbor);
    }
}

void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
}

// DP for coin problem
int minCoins(int coins[], int n, int target) {
    vector<int> dp(target + 1, INT_MAX);
    dp[0] = 0; // Base case: 0 coins to make sum 0

    for (int i = 1; i <= target; ++i) {
        for (int j = 0; j < n; ++j) {
            if (coins[j] <= i && dp[i - coins[j]] != INT_MAX) {
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
            }
        }
    }

    return dp[target] == INT_MAX ? -1 : dp[target];
}

// General knapsack solution
int knapsack(int S, int N, vector<pair<int, int>> &items) {
    vector<int> dp(S + 1, 0);

    for (int i = 0; i < N; ++i) {
        int size = items[i].first;
        int value = items[i].second;

        // Traverse backwards to avoid overwriting needed values
        for (int s = S; s >= size; --s) {
            dp[s] = max(dp[s], dp[s - size] + value);
        }
    }

    return dp[S];
}

// House robber problem
long long house_robber(const vector<long long>& coins) {
    int n = coins.size();
    if (n == 0) return 0;
    if (n == 1) return coins[0];

    vector<long long> dp(n);
    dp[0] = coins[0];
    dp[1] = max(coins[0], coins[1]);

    for (int i = 2; i < n; ++i) {
        dp[i] = max(dp[i - 1], dp[i - 2] + coins[i]);
    }

    return dp[n - 1];
}

// Sum of digits of a number
int sumDigit(int x) {
    int s = 0;
    while (x) {
        s += x % 10;
        x /= 10;
    }
    return s;
}

// Check if a number is beautiful (difference between each digit is at most 2)
bool is_beautiful(ll x) {
    ll y = x % 10;
    x /= 10;
    while (x) {
        if (abs(y - x % 10) > 2) return false;
        y = x % 10;
        x /= 10;
    }
    return true;
}

// Find the max items with the least cost given a budget
int maximizeValue(vector<pair<int, int>>& items, int max_budget) {
    int n = items.size();
    vector<int> dp(max_budget + 1, 0);

    // Sort items by cost (optional, depending on the problem)
    sort(items.begin(), items.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;
    });

    // Iterate through each item
    for (int i = 0; i < n; i++) {
        int value = items[i].first;
        int cost = items[i].second;

        // Update DP table from the end to avoid overwriting values
        for (int j = max_budget; j >= cost; j--) {
            dp[j] = max(dp[j], dp[j - cost] + value);
        }
    }

    // The maximum value achievable with the given budget
    return dp[max_budget];
}

/**
 * Counts the number of positive integer solutions (X,Y,Z) to:
 * aX + b*(Y * cZ) = target
 *
 * @param a Coefficient of X
 * @param b Coefficient of Y*cZ product
 * @param c Multiplier for Z in the product
 * @param target The right-hand side value (could be N, N², etc.)
 * @return Number of valid (X,Y,Z) tuples
 */
ll count_solutions(int a, int b, int c, int target) {
    ll count = 0;
    int max_k = target / b; // Maximum possible value of Y*cZ

    for (int k = 1; k <= max_k; k++) {
        // Check if (target - b*k) is divisible by a
        int remaining = target - b * k;
        if (remaining > 0 && remaining % a == 0) {
            // Now find number of (Y,Z) pairs where Y*(cZ) = k
            // Which is equivalent to Y*Z = k/c

            if (k % c != 0) continue; // k must be divisible by c

            int yz_product = k / c;
            if (yz_product >= 1 && yz_product < N) {
                count += divisors[yz_product];
            }
        }
    }

    return count;
}

/**
 * Solves the knapsack problem with profit adjustment
 * 
 * @param N Number of items
 * @param K Maximum weight capacity
 * @param items Vector of pairs {weight, price} for each item
 * @return Maximum profit (sum of prices minus sum of weights)
 */
int calculateMaxProfit(int N, int K, const vector<pair<int, int>>& items) {
    // dp[i] represents maximum profit achievable with weight i
    vector<int> dp(K + 1, INT_MIN);
    dp[0] = 0; // Base case: 0 weight gives 0 profit
    
    for (const auto& item : items) {
        int w = item.first;
        int p = item.second;
        int net_value = p - w; // Price minus weight (gas cost)
        
        for (int j = K; j >= w; --j) {
            if (dp[j - w] + net_value > dp[j]) {
                dp[j] = dp[j - w] + net_value;
            }
        }
    }
    
    // Return the maximum profit across all possible weights ≤ K
    return *max_element(dp.begin(), dp.end());
}

// Main function
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
#endif

    return 0;
}
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int MOD = 1e9 + 7;
const int N = 1e7;

// Global arrays
int fact[N + 1];    // Factorial
int divisors[N];    // Divisors e.g divisors[6] = 4 (1,2,3,6), divisors[7] = 2 (1,7)
int spf[N];         // Smallest Prime Factor
int prefix[N];      // Prefix Sum
vector<int> adj[N]; // adjacency list
bool visited[N];
bool is_prime[N + 1]; // All Primes from 1 to N
vector<int> prime_prefix(N, 0);

// Basic math operations
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
  if(b == 0) return a;
  return GCD(b,a % b);
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

int nCr(int n, int r) {
  return mul(fact[n], modInverse(mul(fact[r], fact[n - r])));
}

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

// for x = 9 vector has 1 3 9
vector<int> divisorsOfX(int x) {
  vector<int> res;
  int i;
  for (i = 1; i * i < x; i++) {
    if (x % i) continue;
    res.push_back(i);
    res.push_back(x / i);
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
int binarySearch(const vector<int>& arr, int target) {
  int left = 0;
  int right = arr.size() - 1;
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (arr[mid] == target) {
      return mid;
    } else if (arr[mid] < target) {
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

// Problem solution
void solve() {
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n;
    vector<int> speeds(n);
    for (int i = 0; i < n; i++) {
      cin >> speeds[i];
    }
    sort(speeds.begin(), speeds.end());

    cin >> m;
    vector<int> queries(m);
    for (int i = 0; i < m; i++) {
      cin >> queries[i];
    }

    for (int q : queries) {
      auto it = upper_bound(speeds.begin(), speeds.end(), q);
      int count = speeds.end() - it;
      cout << count << " ";
    }
    cout << endl;
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

  #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
  #endif

  solve();
  return 0;
}
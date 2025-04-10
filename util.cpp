#include <bits/stdc++.h>
using namespace std;
#define endl '\n'

int MOD = 1e9 + 7;
const int N = 1e6;

// Global arrays
int fact[N + 1];          // Factorial
int divisors[N];         // Divisors
int spf[N];             // Smallest Prime Factor
int prefix[N];         // Prefix Sum
vector<int> adj[N];   // adjacency list
bool visited[N];

// Section 1: Mathematical Operations and Modular Arithmetic

int mul(int a, int b);
int binary_exp(int x, int p);
int modInverse(int x);
int nCr(int n, int r);
int nPr(int n, int r);

// Section 2: Precomputations and Factorization

void buildF();        // Factorials
void buildD();        // Divisors
void precomputeSPF(); // Smallest Prime Factors
vector<pair<int, int>> primeFactorization(int x);

// Section 3: Graph Algorithms
void dfs(int node);
void bfs(int start);

// Section 4: Prefix Sum and Searching

void buildPrefixSum(const vector<int> &arr);
int rangeSum(int l, int r);
int binarySearch(vector<int> &arr, int target);

// Section 5: Two Pointers Technique
int twoPointersExample(vector<int> &arr, int target);


void solve() {
  int n, x;
  cin >> n;
  vector<int> vec;
  for(int i = 0; i < n; i++) {
    cin >> x;
    vec.push_back(x);
  }
  
  int cntr = 1, temp = vec[0];
  for(int i = 1; i < vec.size(); i++) {
    if(temp <= vec[i]) {
      cntr++;
    }
    temp = vec[i];
  }
  cout << cntr;
}

// MAIN FUNCTION
int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

#ifndef ONLINE_JUDGE
  freopen("input.txt", "r", stdin);
#endif

  solve();

  return 0;
}

// Section 1: Mathematical Operations and Modular Arithmetic
int mul(int a, int b)
{
  return 1LL * a * b % MOD;
}

int binary_exp(int x, int p)
{
  int ret = 1;
  while (p)
  {
    if (p % 2 != 0)
      ret = mul(ret, x);
    x = mul(x, x);
    p /= 2;
  }
  return ret;
}

int modInverse(int x)
{
  return binary_exp(x, MOD - 2);
}

int nCr(int n, int r)
{
  return mul(fact[n], modInverse(mul(fact[r], fact[n - r])));
}

int nPr(int n, int r)
{
  return mul(fact[n], modInverse(fact[n - r]));
}

// Section 2: Precomputations and Factorization
void buildF()
{
  fact[0] = 1;
  for (int i = 1; i <= N; i++)
  {
    fact[i] = mul(fact[i - 1], i);
  }
}

void precomputeSPF()
{
  for (int i = 0; i < N; ++i)
    spf[i] = i;

  for (int i = 2; i * i < N; ++i)
  {
    if (spf[i] == i)
    {
      for (int j = i * i; j < N; j += i)
      {
        if (spf[j] == j)
          spf[j] = i;
      }
    }
  }
}

vector<pair<int, int>> primeFactorization(int x)
{
  vector<pair<int, int>> factors;
  while (x > 1)
  {
    int prime = spf[x];
    int count = 0;
    while (spf[x] == prime)
    {
      x /= prime;
      count++;
    }
    factors.emplace_back(prime, count);
  }
  return factors;
}

void buildD()
{
  for (int i = 1; i < N; ++i)
  {
    for (int j = i; j < N; j += i)
    {
      divisors[j]++;
    }
  }
}

// Section 3: Graph Algorithms
void dfs(int node)
{
  visited[node] = true;
  for (int neighbor : adj[node])
  {
    if (!visited[neighbor])
      dfs(neighbor);
  }
}

void bfs(int start)
{
  queue<int> q;
  q.push(start);
  visited[start] = true;

  while (!q.empty())
  {
    int node = q.front();
    q.pop();
    for (int neighbor : adj[node])
    {
      if (!visited[neighbor])
      {
        visited[neighbor] = true;
        q.push(neighbor);
      }
    }
  }
}

// Section 4: Prefix Sum and Searching
void buildPrefixSum(const vector<int> &arr)
{
  prefix[0] = 0;
  for (int i = 1; i <= arr.size(); ++i)
  {
    prefix[i] = prefix[i - 1] + arr[i - 1];
  }
}

int rangeSum(int l, int r)
{
  return prefix[r] - prefix[l - 1];
}

int binarySearch(vector<int> &arr, int target)
{
  int low = 0, high = arr.size() - 1;
  while (low <= high)
  {
    int mid = (low + high) / 2;
    if (arr[mid] == target)
      return mid;
    else if (arr[mid] < target)
      low = mid + 1;
    else
      high = mid - 1;
  }
  return -1;
}

// Section 5: Two Pointers Technique
int twoPointersExample(vector<int> &arr, int target)
{
  int count = 0;
  int left = 0, right = arr.size() - 1;
  sort(arr.begin(), arr.end());
  while (left < right)
  {
    int sum = arr[left] + arr[right];
    if (sum == target)
    {
      count++;
      left++;
      right--;
    }
    else if (sum < target)
      left++;
    else
      right--;
  }
  return count;
}
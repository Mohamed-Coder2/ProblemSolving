#include <bits/stdc++.h>
using namespace std;

void solve()
{
  int t;
  cin >> t;

  while (t--)
  {
    int n;
    cin >> n;
    vector<int> a(n);
    unordered_map<int, int> freq;

    for (int i = 0; i < n; ++i)
    {
      cin >> a[i];
      freq[a[i]]++;
    }

    unordered_map<int, int> freq_count;
    for (auto &p : freq)
    {
      freq_count[p.second]++;
    }

    vector<int> unique_counts;
    for (auto &p : freq_count)
    {
      unique_counts.push_back(p.first);
    }

    sort(unique_counts.begin(), unique_counts.end());

    int min_removal = n;

    for (int c : unique_counts)
    {
      int to_keep = 0;
      for (auto &p : freq_count)
      {
        if (p.first >= c)
        {
          to_keep += (p.second * c);
        }
      }
      int to_remove = n - to_keep;
      min_removal = min(min_removal, to_remove);
    }

    cout << min_removal << '\n';
  }
}

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

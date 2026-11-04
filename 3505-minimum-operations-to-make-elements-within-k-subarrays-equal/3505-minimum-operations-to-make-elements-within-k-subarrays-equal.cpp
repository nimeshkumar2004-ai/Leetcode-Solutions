class Solution {
public:
    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        multiset<int> L, R;
        long long sumL = 0, sumR = 0;

        auto balance = [&]() {
            int need = (L.size() + R.size() + 1) / 2;

            while ((int)L.size() > need) {
                int v = *L.rbegin();
                L.erase(prev(L.end()));
                sumL -= v;
                R.insert(v);
                sumR += v;
            }

            while ((int)L.size() < need) {
                int v = *R.begin();
                R.erase(R.begin());
                sumR -= v;
                L.insert(v);
                sumL += v;
            }
        };

        auto add = [&](int v) {
            if (L.empty() || v <= *L.rbegin()) {
                L.insert(v);
                sumL += v;
            } else {
                R.insert(v);
                sumR += v;
            }
            balance();
        };

        auto remove = [&](int v) {
            auto it = L.find(v);

            if (it != L.end()) {
                L.erase(it);
                sumL -= v;
            } else {
                it = R.find(v);
                R.erase(it);
                sumR -= v;
            }

            balance();
        };

        vector<long long> cost(n - x + 1);

        for (int i = 0; i < n; i++) {
            add(nums[i]);

            if (i >= x) {
                remove(nums[i - x]);
            }

            if (i >= x - 1) {
                long long median = *L.rbegin();

                cost[i - x + 1] =
                    median * (long long)L.size() - sumL +
                    sumR - median * (long long)R.size();
            }
        }

        const long long INF = 1e18;

        vector<long long> dp(n + 1, 0);
        vector<long long> ndp(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(ndp.begin(), ndp.end(), INF);

            for (int i = 1; i <= n; i++) {
                ndp[i] = ndp[i - 1];

                if (i >= x) {
                    ndp[i] = min(
                        ndp[i],
                        dp[i - x] + cost[i - x]
                    );
                }
            }

            dp.swap(ndp);
        }

        return dp[n];
    }
};
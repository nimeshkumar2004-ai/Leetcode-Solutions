
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        vector<long long> v;

        for (int x : nums) {
            long long y = x;
            v.push_back(y * y);
        }

        sort(v.begin(), v.end());

        long long ans = 0;
        int n = v.size();

        for (int i = 0; i < n; i++) {
            if (i < n / 2) {
                ans -= v[i];
            } else {
                ans += v[i];
            }
        }

        return ans;
    }
};


class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const long long MOD = 1e9 + 7;
        vector<int> bits(32, 0);

        for (int num : nums) {
            for (int i = 0; i < 32; i++) {
                if (num & (1 << i)) {
                    bits[i]++;
                }
            }
        }

        long long ans = 0;

        while (k--) {
            long long num = 0;

            for (int i = 31; i >= 0; i--) {
                if (bits[i] > 0) {
                    num |= (1LL << i);
                    bits[i]--;
                }
            }

            ans = (ans + num * num) % MOD;
        }

        return ans;
    }
};

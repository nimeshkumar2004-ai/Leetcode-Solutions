
class Solution {
public:
    int sortableIntegers(vector<int>& nums) {
        int n = nums.size();

        vector<int> prefMax(n + 1, 0);
        vector<int> suffMin(n + 1, INT_MAX);
        vector<int> prefDrop(n, 0);

        // Prefix maximum
        for (int i = 0; i < n; i++) {
            prefMax[i + 1] = max(prefMax[i], nums[i]);
        }

        // Suffix minimum
        for (int i = n - 1; i >= 0; i--) {
            suffMin[i] = min(nums[i], suffMin[i + 1]);
        }

        // Count adjacent decreasing pairs
        for (int i = 1; i < n; i++) {
            prefDrop[i] = prefDrop[i - 1]
                        + (nums[i - 1] > nums[i]);
        }

        // Check whether block size k is sortable
        auto check = [&](int k) -> bool {
            for (int start = 0; start < n; start += k) {
                int end = start + k - 1;

                int drops = prefDrop[end] - prefDrop[start];

                // Include the circular boundary
                if (nums[end] > nums[start]) {
                    drops++;
                }

                // Block must be sortable by rotation
                if (drops > 1) {
                    return false;
                }

                // Previous elements must not exceed
                // the elements in the remaining suffix
                if (prefMax[start] > suffMin[start]) {
                    return false;
                }
            }
            return true;
        };

        int ans = 0;

        // Check every divisor of n
        for (int d = 1; 1LL * d * d <= n; d++) {
            if (n % d == 0) {
                if (check(d)) {
                    ans += d;
                }

                int other = n / d;
                if (other != d && check(other)) {
                    ans += other;
                }
            }
        }

        return ans;
    }
};

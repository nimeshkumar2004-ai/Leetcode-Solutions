class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        long long totalOps = (long long)k1 + k2;
        
        vector<long long> count(100005, 0);
        long long maxDiff = 0;
        for (int i = 0; i < n; ++i) {
            long long diff = abs(nums1[i] - nums2[i]);
            count[diff]++;
            maxDiff = max(maxDiff, diff);
        }
        
        for (long long d = maxDiff; d > 0 && totalOps > 0; --d) {
            if (count[d] == 0) continue;
            
            long long opsToReduce = min(totalOps, count[d]);
            count[d] -= opsToReduce;
            count[d - 1] += opsToReduce;
            totalOps -= opsToReduce;
        }
        
        long long result = 0;
        for (long long d = 1; d <= maxDiff; ++d) {
            if (count[d] > 0) {
                result += count[d] * d * d;
            }
        }
        
        return result;
    }
};
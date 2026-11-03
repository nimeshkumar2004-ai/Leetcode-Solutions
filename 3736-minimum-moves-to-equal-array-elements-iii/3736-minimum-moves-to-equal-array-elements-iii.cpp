
class Solution {
public:
    int minMoves(vector<int>& nums) {
        int maxi = *max_element(nums.begin(), nums.end());

        int ans = 0;

        for (int x : nums) {
            ans += maxi - x;
        }

        return ans;
    }
};

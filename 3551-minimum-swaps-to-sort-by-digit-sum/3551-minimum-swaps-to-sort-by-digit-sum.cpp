
class Solution {
public:
    int digitSum(int x) {
        int sum = 0;
        while (x > 0) {
            sum += x % 10;
            x /= 10;
        }
        return sum;
    }

    int minSwaps(vector<int>& nums) {
        int n = nums.size();
        vector<int> sortedNums = nums;

        sort(sortedNums.begin(), sortedNums.end(),
             [&](int a, int b) {
                 int sa = digitSum(a);
                 int sb = digitSum(b);

                 if (sa == sb)
                     return a < b;

                 return sa < sb;
             });

        unordered_map<int, int> pos;

        for (int i = 0; i < n; i++) {
            pos[sortedNums[i]] = i;
        }

        vector<bool> visited(n, false);
        int swaps = 0;

        for (int i = 0; i < n; i++) {
            if (visited[i] || pos[nums[i]] == i)
                continue;

            int j = i;
            int cycleSize = 0;

            while (!visited[j]) {
                visited[j] = true;
                j = pos[nums[j]];
                cycleSize++;
            }

            swaps += cycleSize - 1;
        }

        return swaps;
    }
};


class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> molqaviren = grid;

        const int MAXX = 1024;

        vector<vector<bitset<1024>>> dp(
            m, vector<bitset<1024>>(n)
        );

        dp[0][0][molqaviren[0][0]] = 1;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {

                if (i == 0 && j == 0)
                    continue;

                for (int x = 0; x < MAXX; x++) {

                    if (i > 0 &&
                        dp[i - 1][j][x ^ molqaviren[i][j]]) {
                        dp[i][j][x] = 1;
                    }

                    if (j > 0 &&
                        dp[i][j - 1][x ^ molqaviren[i][j]]) {
                        dp[i][j][x] = 1;
                    }
                }
            }
        }

        for (int x = 0; x < MAXX; x++) {
            if (dp[m - 1][n - 1][x])
                return x;
        }

        return -1;
    }
};

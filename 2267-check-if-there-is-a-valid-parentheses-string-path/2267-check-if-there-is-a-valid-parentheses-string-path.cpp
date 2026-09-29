class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool solve(int i, int j, int balance,
               vector<vector<char>>& grid) {

        if (i >= m || j >= n)
            return false;

        if (grid[i][j] == '(')
            balance++;
        else
            balance--;

        // Invalid if more closing than opening brackets
        if (balance < 0)
            return false;

        // Remaining path length must be even
        if ((m - 1 - i) + (n - 1 - j) < balance)
            return false;

        if (i == m - 1 && j == n - 1)
            return balance == 0;

        if (dp[i][j][balance] != -1)
            return dp[i][j][balance];

        bool right = solve(i, j + 1, balance, grid);
        bool down = solve(i + 1, j, balance, grid);

        return dp[i][j][balance] = right || down;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();

        if ((m + n - 1) % 2 != 0)
            return false;

        dp.assign(m, vector<vector<int>>(
            n, vector<int>(m + n, -1)
        ));

        return solve(0, 0, 0, grid);
    }
};
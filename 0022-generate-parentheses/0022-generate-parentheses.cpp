
class Solution {
public:
    void solve(int open, int close, int n, string s,
               vector<string>& ans) {
        
        // Base case
        if (s.length() == 2 * n) {
            ans.push_back(s);
            return;
        }

        // Add opening bracket
        if (open < n) {
            solve(open + 1, close, n, s + "(", ans);
        }

        // Add closing bracket
        if (close < open) {
            solve(open, close + 1, n, s + ")", ans);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> ans;
        solve(0, 0, n, "", ans);
        return ans;
    }
};
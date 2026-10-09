
class Solution {
public:
    int minInsertions(string s) {
        int open = 0;
        int insertions = 0;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                open++;
            } else {
                // Check whether the next character is also ')'
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                } else {
                    insertions++;
                }

                if (open > 0) {
                    open--;
                } else {
                    insertions++;
                }
            }
        }

        return insertions + 2 * open;
    }
};
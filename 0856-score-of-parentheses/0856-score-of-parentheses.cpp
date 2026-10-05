class Solution {
public:
    int scoreOfParentheses(string s) {
        stack<int> st;
        st.push(0);

        for (char c : s) {
            if (c == '(') {
                st.push(0);
            } 
            else {
                int v = st.top();
                st.pop();

                int score = (v == 0) ? 1 : 2 * v;

                st.top() += score;
            }
        }

        return st.top();
    }
};
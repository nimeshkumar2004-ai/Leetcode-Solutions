
class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs in a map
        for (auto &p : knowledge) {
            mp[p[0]] = p[1];
        }

        string ans = "";

        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') {
                string key = "";
                i++;

                // Extract key until closing bracket
                while (s[i] != ')') {
                    key += s[i];
                    i++;
                }

                // Replace key with its value
                if (mp.find(key) != mp.end()) {
                    ans += mp[key];
                } else {
                    ans += "?";
                }
            } else {
                ans += s[i];
            }
        }

        return ans;
    }
};
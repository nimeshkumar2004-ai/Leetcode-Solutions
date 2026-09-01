class Solution {
public:
    string getPermutation(int n, int k) {
        vector<int> list;
        int fact = 1;
        for (int i = 1; i <= n; i++) {
            fact *= i;
            list.push_back(i);
        }
        fact /= n;
        k -= 1;
        string result;
        while (true) {
            result += to_string(list[k / fact]);
            list.erase(list.begin() + (k / fact));
            if (list.empty()) break;
            k %= fact;
            fact /= list.size();
        }
        return result;
    }
};
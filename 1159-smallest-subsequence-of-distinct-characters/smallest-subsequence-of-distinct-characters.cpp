class Solution {
public:
    string smallestSubsequence(string s) {
        int last[26];
        bool used[26] = {false};

        for (int i = 0; i < s.size(); i++)
            last[s[i] - 'a'] = i;

        string ans = "";

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (used[c - 'a'])
                continue;

            while (!ans.empty() &&
                   ans.back() > c &&
                   last[ans.back() - 'a'] > i) {
                used[ans.back() - 'a'] = false;
                ans.pop_back();
            }

            ans += c;
            used[c - 'a'] = true;
        }

        return ans;
    }
};
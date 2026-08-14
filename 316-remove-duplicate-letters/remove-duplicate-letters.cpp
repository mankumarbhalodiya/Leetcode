class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> count(26, 0);
        vector<bool> used(26, false);

        for (char c : s) {
            count[c - 'a']++;
        }

        string st;

        for (char c : s) {
            count[c - 'a']--;

            if (used[c - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   count[st.back() - 'a'] > 0) {

                used[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            used[c - 'a'] = true;
        }

        return st;
    }
};
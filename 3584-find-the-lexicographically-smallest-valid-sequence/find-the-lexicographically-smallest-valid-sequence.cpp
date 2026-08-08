class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // right[i] = position in word1 where word2[i] can be matched
        // while matching word2[i..m-1] from the right.
        vector<int> right(m, -1);

        int j = m - 1;

        for (int i = n - 1; i >= 0 && j >= 0; --i) {
            if (word1[i] == word2[j]) {
                right[j] = i;
                --j;
            }
        }

        vector<int> ans;

        int p = 0;
        bool changed = false;

        for (int i = 0; i < n && p < m; ++i) {
            if (word1[i] == word2[p]) {
                ans.push_back(i);
                ++p;
            }
            else if (!changed) {
                // We change word1[i] to word2[p].
                // The remaining word2[p+1..] must be possible.
                if (p + 1 == m || 
                    (right[p + 1] != -1 && right[p + 1] > i)) {

                    ans.push_back(i);
                    ++p;
                    changed = true;
                }
            }
        }

        return p == m ? ans : vector<int>();
    }
};
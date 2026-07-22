#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Group {
    int start;
    int length;
};

class SparseTable {
private:
    int n;
    vector<vector<int>> st;

public:
    SparseTable(const vector<int>& nums) {
        n = nums.size();
        if (n == 0) return;
        int log = 32 - __builtin_clz(n);
        st.assign(log + 1, vector<int>(n, 0));
        st[0] = nums;
        for (int i = 1; i <= log; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = max(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) const {
        if (l > r || n == 0) return 0;
        int i = 31 - __builtin_clz(r - l + 1);
        return max(st[i][l], st[i][r - (1 << i) + 1]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>>& queries) {
        int n = s.length();
        int ones = 0;
        for (char c : s) if (c == '1') ones++;

        // Preprocess 0-groups and zeroGroupIndex
        vector<Group> zeroGroups;
        vector<int> zeroGroupIndex(n, -1);

        for (int i = 0; i < n; ++i) {
            if (s[i] == '0') {
                if (i > 0 && s[i - 1] == '0') {
                    zeroGroups.back().length++;
                } else {
                    zeroGroups.push_back({i, 1});
                }
            }
            zeroGroupIndex[i] = zeroGroups.empty() ? -1 : (int)zeroGroups.size() - 1;
        }

        if (zeroGroups.empty()) {
            return vector<int>(queries.size(), ones);
        }

        // Sum of lengths of adjacent zero groups
        int g = zeroGroups.size();
        vector<int> zeroMergeLengths(max(0, g - 1), 0);
        for (int i = 0; i < g - 1; ++i) {
            zeroMergeLengths[i] = zeroGroups[i].length + zeroGroups[i + 1].length;
        }

        SparseTable st(zeroMergeLengths);
        vector<int> ans;
        ans.reserve(queries.size());

        for (const auto& q : queries) {
            int l = q[0], r = q[1];

            int left = (s[l] == '0') ? (zeroGroups[zeroGroupIndex[l]].length - (l - zeroGroups[zeroGroupIndex[l]].start)) : -1;
            int right = (s[r] == '0') ? (r - zeroGroups[zeroGroupIndex[r]].start + 1) : -1;

            int startGroupIndex = zeroGroupIndex[l] + 1;
            int endGroupIndex = (s[r] == '0') ? (zeroGroupIndex[r] - 1) : zeroGroupIndex[r];

            int startAdjacentGroupIndex = startGroupIndex;
            int endAdjacentGroupIndex = endGroupIndex - 1;

            int activeSections = ones;

            // Case 1: l and r fall into adjacent zero groups
            if (s[l] == '0' && s[r] == '0' && zeroGroupIndex[l] + 1 == zeroGroupIndex[r]) {
                activeSections = max(activeSections, ones + left + right);
            } 
            // Case 2: Adjacent pairs of zero groups completely inside [l, r]
            else if (startAdjacentGroupIndex <= endAdjacentGroupIndex) {
                activeSections = max(activeSections, ones + st.query(startAdjacentGroupIndex, endAdjacentGroupIndex));
            }

            // Case 3: Partial zero group at l + full next zero group
            if (s[l] == '0' && zeroGroupIndex[l] + 1 <= endGroupIndex) {
                activeSections = max(activeSections, ones + left + zeroGroups[zeroGroupIndex[l] + 1].length);
            }

            // Case 4: Full previous zero group + partial zero group at r
            if (s[r] == '0' && zeroGroupIndex[r] - 1 >= startGroupIndex) {
                activeSections = max(activeSections, ones + right + zeroGroups[zeroGroupIndex[r] - 1].length);
            }

            ans.push_back(activeSections);
        }

        return ans;
    }
};
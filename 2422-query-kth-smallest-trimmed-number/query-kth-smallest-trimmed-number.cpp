class Solution {
public:
    vector<int> smallestTrimmedNumbers(vector<string>& nums, vector<vector<int>>& queries) {
        vector<int> ans;

        for (auto &q : queries) {
            int k = q[0];
            int trim = q[1];

            vector<pair<string, int>> v;

            for (int i = 0; i < nums.size(); i++) {
                string s = nums[i].substr(nums[i].size() - trim);
                v.push_back({s, i});
            }

            sort(v.begin(), v.end(), [](const auto &a, const auto &b) {
                if (a.first == b.first)
                    return a.second < b.second;
                return a.first < b.first;
            });

            ans.push_back(v[k - 1].second);
        }

        return ans;
    }
};
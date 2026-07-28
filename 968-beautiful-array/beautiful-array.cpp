class Solution {
public:
    vector<int> beautifulArray(int n) {
        if (n == 1)
            return {1};

        vector<int> odd = beautifulArray((n + 1) / 2);
        vector<int> even = beautifulArray(n / 2);

        vector<int> ans;

        for (int x : odd)
            ans.push_back(2 * x - 1);

        for (int x : even)
            ans.push_back(2 * x);

        return ans;
    }
};
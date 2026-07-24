class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<vector<bool>> dp(4, vector<bool>(MAXX, false));
        dp[0][0] = true;

        for (int x : nums) {
            vector<vector<bool>> ndp = dp;

            for (int k = 0; k < 3; k++) {
                for (int v = 0; v < MAXX; v++) {
                    if (dp[k][v]) {
                        ndp[k + 1][v ^ x] = true;
                    }
                }
            }

            dp = ndp;
        }

        int ans = 0;
        for (int v = 0; v < MAXX; v++) {
            if (dp[1][v] || dp[3][v])
                ans++;
        }

        return ans;
    }
};
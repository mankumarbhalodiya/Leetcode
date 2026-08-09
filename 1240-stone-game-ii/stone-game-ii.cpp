class Solution {
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();

        // suffix[i] = sum of piles from i to n-1
        vector<int> suffix(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        vector<vector<int>> dp(n, vector<int>(n + 1, -1));

        return solve(0, 1, piles, suffix, dp);
    }

private:
    int solve(int i, int M,
              vector<int>& piles,
              vector<int>& suffix,
              vector<vector<int>>& dp) {

        int n = piles.size();

        // Can take all remaining piles
        if (i >= n || 2 * M >= n - i) {
            return suffix[i];
        }

        if (dp[i][M] != -1) {
            return dp[i][M];
        }

        int opponentBest = INT_MAX;

        // Try taking X piles
        for (int X = 1; X <= 2 * M; X++) {
            int nextM = max(M, X);

            // Opponent gets the best possible score
            opponentBest = min(
                opponentBest,
                solve(i + X, nextM, piles, suffix, dp)
            );
        }

        // Total remaining - opponent's best
        return dp[i][M] = suffix[i] - opponentBest;
    }
};
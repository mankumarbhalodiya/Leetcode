class Solution {
public:
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size();
        const int MOD = 1e9 + 7;

        vector<vector<int>> score(n + 1, vector<int>(n + 1, -1));
        vector<vector<int>> ways(n + 1, vector<int>(n + 1, 0));

        score[n - 1][n - 1] = 0;
        ways[n - 1][n - 1] = 1;

        for (int i = n - 1; i >= 0; i--) {
            for (int j = n - 1; j >= 0; j--) {

                if (board[i][j] == 'X' || (i == n - 1 && j == n - 1))
                    continue;

                int best = max({
                    score[i + 1][j],
                    score[i][j + 1],
                    score[i + 1][j + 1]
                });

                if (best == -1)
                    continue;

                long long cnt = 0;

                if (score[i + 1][j] == best)
                    cnt += ways[i + 1][j];

                if (score[i][j + 1] == best)
                    cnt += ways[i][j + 1];

                if (score[i + 1][j + 1] == best)
                    cnt += ways[i + 1][j + 1];

                ways[i][j] = cnt % MOD;

                int val = 0;
                if (board[i][j] != 'E')
                    val = board[i][j] - '0';

                score[i][j] = best + val;
            }
        }

        if (ways[0][0] == 0)
            return {0, 0};

        return {score[0][0], ways[0][0]};
    }
};
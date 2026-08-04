class Solution {
public:
    void fill(vector<vector<int>>& grid, int r1, int r2, int c1, int c2, int &num) {
        if (r2 - r1 == 1) {
            grid[r1][c1] = num++;
            return;
        }

        int midR = (r1 + r2) / 2;
        int midC = (c1 + c2) / 2;

        // Top-Right
        fill(grid, r1, midR, midC, c2, num);

        // Bottom-Right
        fill(grid, midR, r2, midC, c2, num);

        // Bottom-Left
        fill(grid, midR, r2, c1, midC, num);

        // Top-Left
        fill(grid, r1, midR, c1, midC, num);
    }

    vector<vector<int>> specialGrid(int n) {
        int size = 1 << n;
        vector<vector<int>> grid(size, vector<int>(size));

        int num = 0;
        fill(grid, 0, size, 0, size, num);

        return grid;
    }
};
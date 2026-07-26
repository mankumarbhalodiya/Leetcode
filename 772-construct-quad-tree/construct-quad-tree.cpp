/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {
        val = false;
        isLeaf = false;
        topLeft = topRight = bottomLeft = bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = topRight = bottomLeft = bottomRight = NULL;
    }

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight,
         Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/

class Solution {
public:
    Node* build(vector<vector<int>>& grid, int r, int c, int len) {
        bool same = true;
        int value = grid[r][c];

        for (int i = r; i < r + len && same; i++) {
            for (int j = c; j < c + len; j++) {
                if (grid[i][j] != value) {
                    same = false;
                    break;
                }
            }
        }

        if (same) {
            return new Node(value, true);
        }

        int half = len / 2;

        return new Node(
            true,
            false,
            build(grid, r, c, half),
            build(grid, r, c + half, half),
            build(grid, r + half, c, half),
            build(grid, r + half, c + half, half)
        );
    }

    Node* construct(vector<vector<int>>& grid) {
        return build(grid, 0, 0, grid.size());
    }
};
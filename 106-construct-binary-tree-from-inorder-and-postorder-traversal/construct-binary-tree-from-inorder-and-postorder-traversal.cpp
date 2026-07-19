/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right)
 *         : val(x), left(left), right(right) {}
 * };
 */

class Solution {
public:
    unordered_map<int, int> mp;
    int postIndex;

    TreeNode* solve(vector<int>& inorder, vector<int>& postorder, int left, int right) {
        if (left > right)
            return NULL;

        int rootValue = postorder[postIndex--];
        TreeNode* root = new TreeNode(rootValue);

        int mid = mp[rootValue];

        root->right = solve(inorder, postorder, mid + 1, right);
        root->left = solve(inorder, postorder, left, mid - 1);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        for (int i = 0; i < inorder.size(); i++)
            mp[inorder[i]] = i;

        postIndex = postorder.size() - 1;

        return solve(inorder, postorder, 0, inorder.size() - 1);
    }
};
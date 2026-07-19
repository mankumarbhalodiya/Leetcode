class Solution {
public:
    int preIndex = 0;
    unordered_map<int, int> mp;

    TreeNode* solve(vector<int>& preorder, int left, int right) {
        if (left > right)
            return NULL;

        int val = preorder[preIndex++];
        TreeNode* root = new TreeNode(val);

        int pos = mp[val];

        root->left = solve(preorder, left, pos - 1);
        root->right = solve(preorder, pos + 1, right);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++)
            mp[inorder[i]] = i;

        return solve(preorder, 0, inorder.size() - 1);
    }
};
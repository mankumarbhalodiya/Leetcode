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
    unordered_map<int, int> pos;

    TreeNode* build(vector<int>& preorder, int preStart, int preEnd,
                    vector<int>& postorder, int postStart, int postEnd) {

        if (preStart > preEnd)
            return nullptr;

        TreeNode* root = new TreeNode(preorder[preStart]);

        if (preStart == preEnd)
            return root;

        int leftRoot = preorder[preStart + 1];
        int idx = pos[leftRoot];

        int leftSize = idx - postStart + 1;

        root->left = build(preorder,
                           preStart + 1,
                           preStart + leftSize,
                           postorder,
                           postStart,
                           idx);

        root->right = build(preorder,
                            preStart + leftSize + 1,
                            preEnd,
                            postorder,
                            idx + 1,
                            postEnd - 1);

        return root;
    }

    TreeNode* constructFromPrePost(vector<int>& preorder, vector<int>& postorder) {
        for (int i = 0; i < postorder.size(); i++)
            pos[postorder[i]] = i;

        return build(preorder, 0, preorder.size() - 1,
                     postorder, 0, postorder.size() - 1);
    }
};
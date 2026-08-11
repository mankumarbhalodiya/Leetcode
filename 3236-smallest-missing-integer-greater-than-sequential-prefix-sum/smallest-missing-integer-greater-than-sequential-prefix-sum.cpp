class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];

        // Find sum of longest sequential prefix
        for (int i = 1; i < nums.size(); i++) {
            if (nums[i] == nums[i - 1] + 1)
                sum += nums[i];
            else
                break;
        }

        // Store all elements
        unordered_set<int> st(nums.begin(), nums.end());

        // Find smallest missing integer >= sum
        int x = sum;
        while (st.count(x))
            x++;

        return x;
    }
};
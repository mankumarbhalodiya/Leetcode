class Solution {
public:
    int countElements(vector<int>& nums, int k) {
        int n = nums.size();

        if (k == 0)
            return n;

        sort(nums.begin(), nums.end());

        int ans = 0;

        for (int i = 0; i < n; ) {
            int j = i;

            while (j < n && nums[j] == nums[i])
                j++;

            int greater = n - j;

            if (greater >= k)
                ans += j - i;

            i = j;
        }

        return ans;
    }
};
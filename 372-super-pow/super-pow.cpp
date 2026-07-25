class Solution {
public:
    const int MOD = 1337;

    int power(int a, int b) {
        a %= MOD;
        int res = 1;

        while (b > 0) {
            if (b % 2)
                res = (res * a) % MOD;
            a = (a * a) % MOD;
            b /= 2;
        }

        return res;
    }

    int superPow(int a, vector<int>& b) {
        int ans = 1;

        for (int digit : b) {
            ans = (power(ans, 10) * power(a, digit)) % MOD;
        }

        return ans;
    }
};
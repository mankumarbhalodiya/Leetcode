class Solution {
public:
    long long K;

    // Calculate number of distinct permutations of remaining characters
    long long countWays(vector<int>& freq) {
        int total = 0;
        for (int x : freq) total += x;

        long long ans = 1;

        for (int f : freq) {
            if (f == 0) continue;

            // Multiply by C(total, f)
            long long res = 1;
            for (int i = 1; i <= f; i++) {
                res = res * (total - f + i) / i;
                if (res > K) {
                    res = K;
                    break;
                }
            }

            ans *= res;
            if (ans > K) return K;

            total -= f;
        }

        return ans;
    }

    string smallestPalindrome(string s, int k) {
        K = k;

        vector<int> cnt(26, 0);
        for (char c : s)
            cnt[c - 'a']++;

        vector<int> half(26, 0);
        string mid = "";

        for (int i = 0; i < 26; i++) {
            half[i] = cnt[i] / 2;
            if (cnt[i] % 2)
                mid = char('a' + i);
        }

        if (countWays(half) < k)
            return "";

        string left = "";
        int len = 0;
        for (int x : half) len += x;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;

                long long ways = countWays(half);

                if (ways >= k) {
                    left.push_back(char('a' + c));
                    break;
                } else {
                    k -= ways;
                    half[c]++;
                }
            }
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

class Solution {
private:
    struct Factors {
        int c2 = 0, c3 = 0, c5 = 0, c7 = 0;
    };

    Factors getDigitFactors(int d) {
        Factors f;
        while (d > 0 && d % 2 == 0) { f.c2++; d /= 2; }
        while (d > 0 && d % 3 == 0) { f.c3++; d /= 3; }
        if (d == 5) f.c5++;
        if (d == 7) f.c7++;
        return f;
    }

    int minDigitsNeeded(int c2, int c3, int c5, int c7) {
        int cnt = c5 + c7;
        cnt += c3 / 2;
        c3 %= 2;
        cnt += c2 / 3;
        c2 %= 3;

        if (c3 == 1 && c2 == 1) {
            cnt++;
            c3 = 0; c2 = 0;
        } else if (c3 == 1) {
            cnt++;
            c3 = 0;
        }

        if (c2 == 2) cnt++;
        else if (c2 == 1) cnt++;

        return cnt;
    }

    // Greedily constructs the lexicographically smallest string of length `len`
    // that satisfies the required prime factors.
    string makeSmallest(int r2, int r3, int r5, int r7, int len) {
        string res = "";
        for (int i = 0; i < len; i++) {
            for (int d = 1; d <= 9; d++) {
                Factors df = getDigitFactors(d);
                int next_r2 = max(0, r2 - df.c2);
                int next_r3 = max(0, r3 - df.c3);
                int next_r5 = max(0, r5 - df.c5);
                int next_r7 = max(0, r7 - df.c7);

                int remLen = len - 1 - i;
                if (minDigitsNeeded(next_r2, next_r3, next_r5, next_r7) <= remLen) {
                    res += char('0' + d);
                    r2 = next_r2;
                    r3 = next_r3;
                    r5 = next_r5;
                    r7 = next_r7;
                    break;
                }
            }
        }
        return res;
    }

public:
    string smallestNumber(string num, long long t) {
        Factors req;
        while (t % 2 == 0) { req.c2++; t /= 2; }
        while (t % 3 == 0) { req.c3++; t /= 3; }
        while (t % 5 == 0) { req.c5++; t /= 5; }
        while (t % 7 == 0) { req.c7++; t /= 7; }

        if (t > 1) return "-1";

        int n = num.size();
        vector<Factors> pref(n + 1);
        int firstZero = -1;

        for (int i = 0; i < n; i++) {
            int d = num[i] - '0';
            if (d == 0) {
                firstZero = i;
                break;
            }
            pref[i + 1] = pref[i];
            Factors f = getDigitFactors(d);
            pref[i + 1].c2 += f.c2;
            pref[i + 1].c3 += f.c3;
            pref[i + 1].c5 += f.c5;
            pref[i + 1].c7 += f.c7;
        }

        auto getRem = [&](int i) {
            return Factors{
                max(0, req.c2 - pref[i].c2),
                max(0, req.c3 - pref[i].c3),
                max(0, req.c5 - pref[i].c5),
                max(0, req.c7 - pref[i].c7)
            };
        };

        // Case 1: Check if num itself works
        if (firstZero == -1) {
            Factors rem = getRem(n);
            if (minDigitsNeeded(rem.c2, rem.c3, rem.c5, rem.c7) == 0)
                return num;
        }

        // Case 2: Try matching prefix of length `i`
        int limit = (firstZero == -1) ? n - 1 : firstZero;
        for (int i = limit; i >= 0; i--) {
            Factors rem = getRem(i);
            for (int d = (num[i] - '0') + 1; d <= 9; d++) {
                Factors cur = getDigitFactors(d);
                int r2 = max(0, rem.c2 - cur.c2);
                int r3 = max(0, rem.c3 - cur.c3);
                int r5 = max(0, rem.c5 - cur.c5);
                int r7 = max(0, rem.c7 - cur.c7);

                int remLen = n - i - 1;
                if (minDigitsNeeded(r2, r3, r5, r7) <= remLen) {
                    string prefix = num.substr(0, i) + char('0' + d);
                    string suffix = makeSmallest(r2, r3, r5, r7, remLen);
                    return prefix + suffix;
                }
            }
        }

        // Case 3: Need a longer length > n
        int targetLen = max(n + 1, minDigitsNeeded(req.c2, req.c3, req.c5, req.c7));
        return makeSmallest(req.c2, req.c3, req.c5, req.c7, targetLen);
    }
};
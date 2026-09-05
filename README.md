## Overview

The goal of this problem is to find the **smallest stable index** in an array.

An index `i` is considered stable if the difference between the maximum value in the left part (`nums[0...i]`) and the minimum value in the right part (`nums[i...n-1]`) is at most `k`.

To solve this efficiently, we maintain:
- A **suffix minimum array** to quickly find the minimum value from each index to the end.
- A **running prefix maximum** while traversing the array from left to right.

The first index satisfying the condition is returned. If no such index exists, we return `-1`.

This approach solves the problem in **O(n) time** with **O(n) extra space**.

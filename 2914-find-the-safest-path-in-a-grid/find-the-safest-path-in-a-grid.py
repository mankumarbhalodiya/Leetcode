class Solution:
    def maximumSafenessFactor(self, grid):
        from collections import deque

        n = len(grid)

        # Distance from nearest thief
        dist = [[-1] * n for _ in range(n)]
        q = deque()

        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    dist[i][j] = 0
                    q.append((i, j))

        directions = [(1,0), (-1,0), (0,1), (0,-1)]

        while q:
            x, y = q.popleft()

            for dx, dy in directions:
                nx = x + dx
                ny = y + dy

                if 0 <= nx < n and 0 <= ny < n and dist[nx][ny] == -1:
                    dist[nx][ny] = dist[x][y] + 1
                    q.append((nx, ny))


        # Check path with given safeness
        def canReach(value):

            if dist[0][0] < value:
                return False

            visited = [[False] * n for _ in range(n)]

            q = deque()
            q.append((0, 0))
            visited[0][0] = True

            while q:
                x, y = q.popleft()

                if x == n-1 and y == n-1:
                    return True

                for dx, dy in directions:
                    nx = x + dx
                    ny = y + dy

                    if (0 <= nx < n and 
                        0 <= ny < n and
                        not visited[nx][ny] and
                        dist[nx][ny] >= value):

                        visited[nx][ny] = True
                        q.append((nx, ny))

            return False


        # Binary search maximum safeness
        left = 0
        right = 2 * n
        ans = 0

        while left <= right:

            mid = (left + right) // 2

            if canReach(mid):
                ans = mid
                left = mid + 1
            else:
                right = mid - 1

        return ans
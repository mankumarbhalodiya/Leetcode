class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int, int>>> graph(n + 1);

        for (auto &road : roads) {
            int u = road[0];
            int v = road[1];
            int d = road[2];
            graph[u].push_back({v, d});
            graph[v].push_back({u, d});
        }

        vector<bool> visited(n + 1, false);
        stack<int> st;
        st.push(1);
        visited[1] = true;

        int ans = INT_MAX;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            for (auto &edge : graph[node]) {
                int nei = edge.first;
                int dist = edge.second;

                ans = min(ans, dist);

                if (!visited[nei]) {
                    visited[nei] = true;
                    st.push(nei);
                }
            }
        }

        return ans;
    }
};
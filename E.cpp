#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// 存储图的邻接表
vector<vector<int> > graph;
// 存储每个节点的深度
vector<int> depth;
// 存储每个节点的父节点
vector<int> parent;

// 预处理深度和父节点
void dfs(int u, int p, int d) {
    depth[u] = d;
    parent[u] = p;
    for (int v : graph[u]) {
        if (v!= p) {
            dfs(v, u, d + 1);
        }
    }
}

// 找到两个节点的最近公共祖先
int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }
    while (depth[u] > depth[v]) {
        u = parent[u];
    }
    while (u!= v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

// 计算满足三角形条件的x的数量
int countValidX(int a, int b) {
    if (a > b) {
        swap(a, b);
    }
    return min(a + b - 1, max(a, b)) - max(b - a, 1) + 1;
}

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        // 初始化
        graph.assign(n + 1, vector<int>());
        depth.assign(n + 1, 0);
        parent.assign(n + 1, 0);

        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }

        // 预处理深度和父节点
        dfs(1, 0, 1);

        int result = 0;
        for (int i = 1; i <= n - 1; i++) {
            for (int j = i + 1; j <= n; j++) {
                int l = lca(i, j);
                int distI = depth[i] - depth[l];
                int distJ = depth[j] - depth[l];
                if (i!= l && j!= l) {
                    result += countValidX(distI, distJ);
                }
            }
        }

        cout << result << endl;
    }

    return 0;
}

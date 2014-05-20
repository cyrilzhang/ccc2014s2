// CCC 2014 Stage 2
// Day 1, Problem 3: Werewolf
// Brian Bi

// Idea: tree DP where state is (node, number of wolves in subtree, whether this
// node is wolf or not) and value is # of assignments such that no wolf in
// this subtree accuses a wolf or defends a civilian. Add an extra node 0
// that accuses all the source/root nodes, for the sake of convenience; then
// dp[0][K][0] is the answer. O(NK^2)

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>

using namespace std;

const int MOD = 1000000007;
const int maxN = 200;

int main() {
    int N, K, M; scanf("%d %d %d", &N, &K, &M);
    vector<pair<int,int> > edge[maxN+1];
    int outdeg[maxN+1] = {0};
    int parent[maxN+1] = {0};
    long long dp[maxN+1][maxN+1][2] = {0};
    for (int i = 1; i <= M; i++) {
        char c; int a, b;
        scanf(" %c %d %d", &c, &a, &b);
        edge[a].push_back(make_pair(b, (int)(c == 'A')));
        outdeg[a]++; parent[b] = a;
    }
    queue<int> q;
    vector<int> top;
    // add extra edges from dummy 0 node, then topological sort
    for (int i = 1; i <= N; i++) {
        if (parent[i] == 0) {
            edge[0].push_back(make_pair(i, 0));
            outdeg[0]++;
        }
        if (outdeg[i] == 0) {
            q.push(i);
        }
    }
    while (!q.empty()) {
        int node = q.front(); q.pop();
        top.push_back(node);
        if (node > 0 && --outdeg[parent[node]] == 0) {
            q.push(parent[node]);
        }
    }
    for (int i = 0; i < top.size(); i++) {
        int node = top[i];
        dp[node][0][0] = dp[node][1][1] = 1;
        for (int j = 0; j < edge[node].size(); j++) {
            int child = edge[node][j].first;
            int acc = edge[node][j].second;
            // loop in reverse order so we don't need any extra memory
            for (int k = K; k >= 0; k--) {
                long long res0 = 0;
                long long res1 = 0;
                for (int m = 0; m <= k; m++) {
                    res0 += dp[node][k-m][0]*(dp[child][m][0] +
                                              dp[child][m][1]);
                    // if node is mafia, child is mafia iff this is a defense
                    res1 += dp[node][k-m][1]*dp[child][m][!acc];
                    res0 %= MOD; res1 %= MOD;
                }
                dp[node][k][0] = res0;
                dp[node][k][1] = res1;
            }
        }
    }
    printf("%lld\n", dp[0][K][0]);
}


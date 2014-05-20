// CCC 2014 Stage 2
// Day 1, Problem 2: King Gruff
// Brian Bi

// Idea: Compute shortest path trees forward from A and backward from B.
// The shortest path that uses an edge (u, v) consists of a shortest path from
// A to u + (u, v) + a shortest path from v to B. Rest is straightforward
// partial sums + binary search. O(M log N + Q log M)
#include <cstdio>
#include <queue>
#include <algorithm>
#include <utility>
#include <functional>
using namespace std;
const int maxN = 100010;
const int INF = 2.1e9;
struct Road {
    int x;
    int y;
    int l;
    int c;
};
void dijkstra(int source, vector<pair<int, int> > adj[], vector<int>& dist) {
    fill(dist.begin(), dist.end(), INF);
    priority_queue<pair<int, int>, vector<pair<int, int> >,
                   greater<pair<int, int> > > Q;
    Q.push(make_pair(0, source));
    while (!Q.empty()) {
        pair<int, int> P = Q.top(); Q.pop();
        int d = P.first, u = P.second;
        if (dist[u] <= d) continue;
        dist[u] = d;
        for (int i = 0; i < adj[u].size(); i++) {
            pair<int, int> P2(d + adj[u][i].first, adj[u][i].second);
            if (dist[P2.second] > P2.first) {
                Q.push(P2);
            }
        }
    }
}
int main() {
    int N, M, A, B;
    scanf("%d %d %d %d", &N, &M, &A, &B); A--; B--;
    vector<pair<int,int> > adj[maxN];
    vector<pair<int,int> > radj[maxN];
    vector<Road> roads;
    for (int i = 0; i < M; i++) {
        Road r;
        scanf("%d %d %d %d", &r.x, &r.y, &r.l, &r.c); r.x--; r.y--;
        adj[r.x].push_back(make_pair(r.l, r.y));
        radj[r.y].push_back(make_pair(r.l, r.x));
        roads.push_back(r);
    }
    // Dijkstra's forward from A and backward from B
    vector<int> dist(N);
    vector<int> rdist(N);
    dijkstra(A, adj, dist);
    dijkstra(B, radj, rdist);
    // (length of shortest path using this road, cost to shut down road)
    vector<pair<int, int> > shortest;
    for (int i = 0; i < M; i++) {
        int length;
        if (dist[roads[i].x] == INF || rdist[roads[i].y] == INF) {
            length = INF;
        } else {
            length = dist[roads[i].x] + rdist[roads[i].y] + roads[i].l;
        }
        shortest.push_back(make_pair(length, roads[i].c));
    }
    sort(shortest.begin(), shortest.end());

    vector<int> psum(M + 1);
    for (int i = 1; i <= M; i++) {
        psum[i] = psum[i-1] + shortest[i-1].second;
    }
    int Q; scanf("%d", &Q);
    while (Q--) {
        int D; scanf("%d", &D);
        int idx = upper_bound(shortest.begin(), shortest.end(),
                              make_pair(D, INF)) - shortest.begin();
        printf("%d\n", psum[idx]);
    }
}

// https://www.luogu.com.cn/problem/P3366
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using std::vector;
using std::priority_queue;

int to[400000];
int next[400000];
int weight[400000];
int head[5000];
int cnt;
struct Edge
{
    int to, weight;
    Edge(int to, int weight): to(to), weight(weight) {}
    bool operator<(const Edge &edge) const
    {
        return weight > edge.weight;
    }
};
int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    vector<bool> visited(N, false);
    cnt = 1;
    memset(head, 0, N*sizeof(int));
    priority_queue<Edge> q;
    for (int i = 0; i < M; ++i)
    {
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        --v1; --v2;
        to[cnt] = v2;
        next[cnt] = head[v1];
        weight[cnt] = w;
        head[v1] = cnt++;

        to[cnt] = v1;
        next[cnt] = head[v2];
        weight[cnt] = w;
        head[v2] = cnt++;
    }
    int sz = 1;
    int totalDistance = 0;
    visited[0] = true;
    for (int currIdx = head[0]; currIdx != 0; currIdx = next[currIdx])
    {
        int t = to[currIdx], w = weight[currIdx];
        q.emplace(Edge(t, w));
    }
    while (sz < N && !q.empty())
    {
        while(!q.empty() && visited[q.top().to])
        {
            q.pop();
        }
        if (q.empty())
        {
            printf("orz\n");
            return 0;
        }
        Edge e = q.top(); q.pop();
        visited[e.to] = true;
        totalDistance += e.weight;
        ++sz;
        for (int currIdx = head[e.to]; currIdx != 0; currIdx = next[currIdx])
        {
            q.emplace(Edge(to[currIdx], weight[currIdx]));
        }
    }
    printf("%d\n", totalDistance);
    return 0;
}
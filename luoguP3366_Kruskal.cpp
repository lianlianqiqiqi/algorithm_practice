// https://www.luogu.com.cn/problem/P3366

#include <cstdio>
#include <vector>
#include <queue>
using std::priority_queue;
using std::vector;

struct Edge
{
    int v1;
    int v2;
    int weight;
    Edge(int v1, int v2, int weight) : v1(v1), v2(v2), weight(weight) {}
    bool operator<(const Edge &edge) const
    {
        return weight > edge.weight;
    }
};

int find(int i, vector<int> &father)
{
    if (father[i] == i)
    {
        return i;
    }
    father[i] = find(father[i], father);
    return father[i];
}
bool isSameSet(int i, int j, vector<int> &father)
{
    return find(i, father) == find(j, father);
}
void add(int i, int j, vector<int> &father)
{
    int iFather = find(i, father);
    int jFather = find(j, father);
    father[jFather] = iFather;
}
int main()
{
    int N, M;
    scanf("%d %d", &N, &M);

    vector<int> father(N);
    vector<int> count(N, 1);
    priority_queue<Edge> edges;
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
    for (int i = 0; i < M; ++i)
    {
        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);
        v1 -= 1;
        v2 -= 1;
        edges.emplace(Edge(v1, v2, weight));
        if (!isSameSet(v1, v2, father))
        {
            count[find(v1, father)] += count[find(v2, father)];
            add(v1, v2, father);
        }
    }
    if (count[find(0, father)] != N)
    {
        printf("orz\n");
        return 0;
    }
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
    int sz = 0;
    int totalDistance = 0;
    while (sz < N - 1)
    {
        Edge edge = edges.top();
        edges.pop();
        if (!isSameSet(edge.v1, edge.v2, father))
        {
            add(edge.v1, edge.v2, father);
            totalDistance += edge.weight;
            sz++;
        }
    }
    printf("%d\n", totalDistance);
    return 0;
}
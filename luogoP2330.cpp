// https://www.luogu.com.cn/problem/P2330
#include <vector>
#include <cstdio>
#include <algorithm>
using std::vector;
struct Edge
{
    int from, to, weight;
    Edge(int from, int to, int weight) : from(from), to(to), weight(weight) {}
    bool operator<(const Edge &edge) const
    {
        return weight > edge.weight;
    }
};
int find(int i, vector<int>& father)
{
    if (i == father[i])
    {
        return i;
    }
    father[i] = find(father[i], father);
    return father[i];
}
int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    vector<Edge> q;
    vector<int> father(N);
    for (int i = 0; i < N; ++i)
    {
        father[i] = i;
    }
    for (int i = 0; i < M; ++i)
    {
        int f, t, w;
        scanf("%d %d %d", &f, &t, &w);
        q.emplace_back(Edge(f-1, t-1, w));
    }
    std::sort(q.begin(), q.end(),[](Edge &edge1, Edge &edge2)
                      { return edge1.weight < edge2.weight; });
    int edgeNum = 0;
    int i = 0;
    int currMax = 0;
    while (edgeNum < N - 1)
    {
        for (;i < M;++i)
        {
            Edge& e = q[i];
            int fatherF = find(e.from, father), fatherT = find(e.to, father);
            if (fatherF != fatherT)
            {
                father[fatherT] = fatherF;
                ++edgeNum;
                currMax = e.weight;
            }
        }
    }
    printf("%d %d\n", edgeNum, currMax);
    return 0;
}
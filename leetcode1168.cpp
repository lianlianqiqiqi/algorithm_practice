// https://leetcode.cn/problems/optimize-water-distribution-in-a-village/
#include <vector>
#include <algorithm>
using std::vector;
class Solution
{
private:
    vector<int> father;
    int find(int i)
    {
        if (i == father[i])
        {
            return i;
        }
        father[i] = find(father[i]);
        return father[i];
    }
public:
    int minCostToSupplyWater(int n, vector<int> &wells, vector<vector<int>> &pipes)
    {
        father = vector<int>(n+1);
        int edgeNum = 0;
        int cost = 0;
        vector<vector<int>> q;
        q.reserve(n + pipes.size());
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
            q.emplace_back(vector<int>{i+1, n+1, wells[i]});
        }
        father[n] = n;

        for (vector<int> &pipe : pipes)
        {
            q.emplace_back(pipe);
        }
        std::ranges::sort(q, [](const vector<int> &a, const vector<int> &b)
                          {
                              return a[2] < b[2]; // Sort by cost
                          });
        for (const vector<int> &topElement : q)
        {
            if (edgeNum == n)
            {
                break;
            }
            int v1 = topElement[0] - 1, v2 = topElement[1] - 1, c = topElement[2];
            int v1Father = find(v1), v2Father = find(v2);
            if (v1Father != v2Father)
            {
                cost += c;
                father[v2Father] = v1Father;
                ++edgeNum;
            }
        }
        return cost;
    }
};
// https://leetcode.cn/problems/checking-existence-of-edge-length-limited-paths/
#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
private:
    int find(int i, vector<int>& father)
    {
        if (i == father[i])
        {
            return i;
        }
        father[i] = find(father[i], father);
        return father[i];
    }
public:
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>> &queries)
    {
        const int edgeLen = edgeList.size();
        const int queriesLen = queries.size();
        vector<int> queriesIdx(queriesLen);
        vector<int> father(n);
        vector<bool> result(queriesLen);
        for (int i = 0; i < n; ++i)
        {
            father[i] = i;
        }
        for (int i = 0; i < queriesLen; ++i)
        {
            queriesIdx[i] = i;
        }
        std::ranges::sort(queriesIdx, [&queries](int i, int j){
            return queries[i][2] < queries[j][2];
        });
        std::ranges::sort(edgeList, [](vector<int>& a, vector<int>& b){
            return a[2] < b[2];
        });
        int i = 0;
        for (int ii = 0; ii < queriesLen; ++ii)
        {
            int queryIdx = queriesIdx[ii];
            const int queryLen = queries[queryIdx][2], v1 = queries[queryIdx][0], v2 = queries[queryIdx][1];
            for (; i < edgeLen && edgeList[i][2] < queryLen; ++i)
            {
                int edgeV1 = edgeList[i][0], edgeV2 = edgeList[i][1];
                int v1Father = find(edgeV1, father), v2Father = find(edgeV2, father);
                father[v2Father] = v1Father;
            }
            result[queryIdx] = find(v1, father) == find(v2, father);
        }
        return result;
    }
};
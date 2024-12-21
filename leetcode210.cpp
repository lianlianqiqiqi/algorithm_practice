// https://leetcode.cn/problems/course-schedule-ii/
#include <vector>
using std::vector;

class Solution
{
public:
    vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
    {
        const int EDGE_NUM = prerequisites.size();
        int *head = new int[numCourses];
        int *next = new int[EDGE_NUM + 1];
        int *to = new int[EDGE_NUM + 1];
        vector<int> result(numCourses);
        int *inDegree = new int[numCourses];
        int cnt = 1;
        int resultSz = 0;
        memset(head, 0, numCourses * sizeof(int));
        memset(inDegree, 0, numCourses * sizeof(int));

        for (auto &info : prerequisites)
        {
            int start = info[1], end = info[0];
            to[cnt] = end;
            next[cnt] = head[start];
            head[start] = cnt++;
            inDegree[end]++;
        }
        for (int i = 0; i < numCourses; ++i)
        {
            if (inDegree[i] == 0)
                result[resultSz++] = i;
        }
        for (int i = 0; i < resultSz; ++i)
        {
            int startPoint = result[i];
            int edgeIdx = head[startPoint];
            while (edgeIdx != 0)
            {
                if (--inDegree[to[edgeIdx]] == 0)
                    result[resultSz++] = to[edgeIdx];
                edgeIdx = next[edgeIdx];
            }
        }
        return resultSz == numCourses ? result : vector<int>(0);
    }
};
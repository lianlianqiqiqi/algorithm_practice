// https://leetcode.cn/problems/parallel-courses-iii/
#include<vector>
#include<algorithm>
using std::vector;

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        const int M = relations.size();
        int cnt = 1;
        int* to = new int[M+1];
        int* next = new int[M+1];
        int* head = new int [n+1];
        int* inDegree = new int[n+1];
        memset(head, 0, (n+1)*sizeof(int));
        memset(inDegree, 0, (n+1)*sizeof(int));
        int* q = new int[n];
        int* minTime = new int[n+1];
        std::fill(minTime, minTime+n+1, 0);
        int result = 0;
        
        int sz = 0, left = 0;
        for (vector<int>& relation: relations)
        {
            int f = relation[0], t = relation[1];
            to[cnt] = t;
            next[cnt] = head[f];
            head[f] = cnt++;
            ++inDegree[t];
        }
        for (int i = 1; i <= n; ++i) 
        {
            if (inDegree[i] == 0)
            {
                q[sz++] = i;
                minTime[i] = time[i-1];
                result = std::max(result, minTime[i]);
            }
        }
        while (sz < n)
        {
            int curr = q[left++];
            int cntIdx = head[curr];
            while (cntIdx != 0)
            {
                int t = to[cntIdx];
                if (minTime[curr] + time[t-1] > minTime[t])
                {
                    minTime[t] = minTime[curr] + time[t-1];
                }
                if (--inDegree[t] == 0)
                {
                    q[sz++] = t;
                    result = std::max(result, minTime[t]);
                }
                cntIdx = next[cntIdx];
            }
        }
        return result;
    }
};
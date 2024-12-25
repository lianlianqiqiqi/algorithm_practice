// https://leetcode.cn/problems/loud-and-rich/
#include<vector>
#include<cstring>
using std::vector;

class Solution {
public:
    vector<int> loudAndRich(vector<vector<int>>& richer, vector<int>& quiet) 
    {
        const int N = quiet.size(), M = richer.size();
        int cnt = 1;
        int* to = new int[M+1];
        int* next = new int[M+1];
        int* head = new int[N];
        int* inDegree = new int[N];
        memset(head, 0, N*sizeof(int));
        memset(inDegree, 0, N*sizeof(int));
        vector<int> result(N);
        vector<int> q(N);
        for (int i = 0; i < N; ++i)
        {
            result[i] = i;
        }
        for (vector<int>& rich: richer)
        {
            int f = rich[0], t = rich[1];
            to[cnt] = t;
            next[cnt] = head[f];
            head[f] = cnt++;
            ++inDegree[t];
        }
        int sz = 0, left = 0;
        for (int i = 0; i < N; ++i)
        {
            if (inDegree[i] == 0)
            {
                q[sz++] = i;
            }
        }
        while (sz < N)
        {
            int f = q[left++];
            int nextIdx = head[f];
            while (nextIdx != 0)
            {
                int t = to[nextIdx];
                int minFIdx = result[f];
                if (quiet[minFIdx] < quiet[result[t]])
                {
                    result[t] = minFIdx;
                }
                if (--inDegree[t] == 0)
                {
                    q[sz++] = t;
                }
                nextIdx = next[nextIdx];
            }
        }
        return result;
    }
};
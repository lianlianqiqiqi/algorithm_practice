// https://leetcode.cn/problems/stamping-the-sequence/
#include <string>
#include <vector>
#include <bitset>
using std::string;
using std::vector;
class Solution
{
private:
    int cnt = 1;
    int to[50000];
    int next[50000];
public:
    vector<int> movesToStamp(string stamp, string target)
    {
        cnt = 1;
        std::bitset<1000> visited(0);
        const int targetLen = target.size(), stampLen = stamp.size();
        int startLowerBound = 0, startUpperBound = targetLen - stampLen;
        const int intervalSize = startUpperBound - startLowerBound + 1;
        vector<int> result(intervalSize);
        int* mistake = new int[intervalSize];
        int* head = new int[targetLen];
        memset(mistake, 0, sizeof(int)*intervalSize);
        memset(head, 0, sizeof(int)*targetLen);
        int sz = 0;
        for (int i = startLowerBound; i <= startUpperBound; ++i)
        {
            for (int j = 0; j < stampLen; ++j)
            {
                if (target[i+j] != stamp[j])
                {
                    ++mistake[i];
                    to[cnt] = i;
                    next[cnt] = head[i+j];
                    head[i+j] = cnt++;
                }
            }
            if (mistake[i] == 0)
            {
                result[intervalSize - (++sz)] = i;
            }
        }
        if (sz == 0) return {};
        int right = intervalSize - 1;
        while (sz < intervalSize)
        {
            int currStart = result[right--];
            for (int i = currStart; i < currStart + stampLen; ++i)
            {
                if (!visited[i])
                {
                    visited[i] = true;
                    int idx = head[i];
                    while (idx != 0)
                    {
                        int t = to[idx];
                        --mistake[t];
                        if (mistake[t] == 0)
                        {
                            result[intervalSize - (++sz)] = t;
                        }
                        idx = next[idx];
                    }
                }
            }
            if (right < intervalSize - sz)
            {
                return {};
            }
        }
        return result;
    }
};
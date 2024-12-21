// https://leetcode.cn/problems/alien-dictionary/
#include <vector>
#include <string>
using std::string;
using std::vector;

class Solution
{
public:
    string alienOrder(vector<string> &ws)
    {
        int head[123];
        int inDegree[123];
        int next[100000];
        int to[100000];
        int cnt = 1;
        const int alphaS = 97, alphaE = 122;
        const int N = ws.size();
        int alphaNum = 0;
        memset(head + 97, 0, 26 * sizeof(int));
        memset(inDegree + 97, 0xFF, 26 * sizeof(int));
        for (string &s : ws)
        {
            const int s_sz = s.size();
            for (int i = 0; i < s_sz; ++i)
                inDegree[s[i]] = 0;
        }
        for (int i = alphaS; i <= alphaE; ++i)
        {
            alphaNum += inDegree[i] == 0;
        }
        for (int i = 0; i < N - 1; ++i)
        {
            string &s_pre = ws[i];
            string &s_next = ws[i + 1];
            int min_sz = std::min(s_pre.size(), s_next.size());
            int j;
            for (j = 0; j < min_sz; ++j)
            {
                if (s_pre[j] != s_next[j])
                {
                    int c_first = s_pre[j], c_next = s_next[j];
                    ++inDegree[c_next];
                    to[cnt] = c_next;
                    next[cnt] = head[c_first];
                    head[c_first] = cnt++;
                    break;
                }
            }
            if (j < s_pre.size() && j == s_next.size())
                return "";
        }
        int sz = 0;
        string res(alphaNum, ' ');
        for (int i = alphaS; i <= alphaE; ++i)
        {
            if (inDegree[i] == 0)
                res[sz++] = i;
        }
        for (int i = 0; i < sz; ++i)
        {
            int start = res[i];
            int ii = head[start];
            while (ii != 0)
            {
                int end = to[ii];
                if (--inDegree[end] == 0)
                    res[sz++] = end;
                ii = next[ii];
            }
        }
        return sz == alphaNum ? res : "";
    }
};
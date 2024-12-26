// https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/
#include <vector>
using std::vector;

class Solution
{
public:
    int maximumInvitations(vector<int> &favorite)
    {
        const int N = favorite.size();
        vector<int> inDegree(N, 0);
        vector<int> hang(N, 0);
        int total = 0;
        int circle = 0;
        for (int i = 0; i < N; ++i)
        {
            ++inDegree[favorite[i]];
        }
        vector<int> zeroInDegree(N);
        int sz = 0;
        for (int i = 0; i < N; ++i)
        {
            if (inDegree[i] == 0)
            {
                zeroInDegree[sz++] = i;
            }
        }
        for (int left = 0; left < sz; ++left)
        {
            int currZero = zeroInDegree[left];
            int currFavorite = favorite[currZero];
            hang[currFavorite] = std::max(hang[currFavorite], hang[currZero]+1);
            if (--inDegree[currFavorite] == 0)
            {
                zeroInDegree[sz++] = currFavorite;
            }
        }
        for (int i = 0; i < N; ++i)
        {
            if (inDegree[i] != 0)
            {
                if (favorite[favorite[i]] == i)
                {
                    total += hang[i] + hang[favorite[i]] + 2;
                    inDegree[i] = 0;
                    inDegree[favorite[i]] = 0;
                }
                else
                {
                    int sz = 1;
                    inDegree[i] = 0;
                    for (int j = favorite[i]; j != i; j = favorite[j])
                    {
                        ++sz;
                        inDegree[j] = 0;
                    }
                    circle = std::max(circle, sz);
                }
            }
        }
        return std::max(total, circle);
    }
};
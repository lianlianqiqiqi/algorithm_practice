// https://leetcode.cn/problems/as-far-from-land-as-possible/
#include <vector>
#include <cstring>
using std::vector;

class Solution
{
private:
    int queue[10000][2];
    int l = 0, r = 0;
    bool visited[100][100];
public:
    int maxDistance(vector<vector<int>> &grid)
    {
        l = 0;
        r = 0;
        memset(visited, 0, 10000);
        const int n = grid.size();
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (grid[i][j] == 1)
                {
                    queue[r][0] = i;
                    queue[r++][1] = j;
                }
            }
        }
        if (r == n*n || r == 0) return -1;
        int level = -1;
        while (l != r)
        {
            ++level;
            int sz = r - l;
            for (int i = 0; i < sz; ++i)
            {
                int x = queue[l][0], y = queue[l++][1];
                if (x > 0 && grid[x-1][y] == 0 && !visited[x-1][y])
                {
                    queue[r][0] = x-1;
                    queue[r++][1] = y;
                    visited[x-1][y] = true;
                }
                if (x < n - 1 && grid[x+1][y] == 0 && !visited[x+1][y])
                {
                    queue[r][0] = x+1;
                    queue[r++][1] = y;
                    visited[x+1][y] = true;
                }
                if (y > 0 && grid[x][y-1] == 0 && !visited[x][y-1])
                {
                    queue[r][0] = x;
                    queue[r++][1] = y-1;
                    visited[x][y-1] = true;
                }
                if (y < n - 1 && grid[x][y+1] == 0 && !visited[x][y+1])
                {
                    queue[r][0] = x;
                    queue[r++][1] = y+1;
                    visited[x][y+1] = true;
                }
            }
        }
        return level;
    }
};
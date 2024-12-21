// https://leetcode.cn/problems/making-a-large-island/
#include <vector>
#include <algorithm>
using std::vector;

class Solution
{
private:
    int N = 0;
    int dfs(int i, int j, int no, vector<vector<int>> &grid)
    {
        if (i < 0 || i >= N || j < 0 || j >= N || grid[i][j] != 1)
            return 0;
        grid[i][j] = no;
        return dfs(i - 1, j, no, grid) + dfs(i + 1, j, no, grid) + dfs(i, j - 1, no, grid) + dfs(i, j + 1, no, grid) + 1;
    }

public:
    int largestIsland(vector<vector<int>> &grid)
    {
        N = grid.size();
        vector<int> islandSize(2, 0);
        int no = 1;
        int maxArea = 0;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 1)
                    islandSize.push_back(dfs(i, j, ++no, grid));
            }
        }
        bool hasZero = false;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (grid[i][j] == 0)
                {
                    hasZero = true;
                    int uniqueIslands[4];
                    int count = 0;
                    if (i > 0 && grid[i - 1][j] > 1)
                    {
                        uniqueIslands[count++] = grid[i - 1][j];
                    }
                    if (i < N - 1 && grid[i + 1][j] > 1)
                    {
                        int id = grid[i + 1][j];
                        bool dup = false;
                        for (int k = 0; k < count; ++k)
                        {
                            if (uniqueIslands[k] == id)
                            {
                                dup = true;
                                break;
                            }
                        }
                        if (!dup)
                            uniqueIslands[count++] = id;
                    }
                    if (j > 0 && grid[i][j - 1] > 1)
                    {
                        int id = grid[i][j - 1];
                        bool dup = false;
                        for (int k = 0; k < count; ++k)
                        {
                            if (uniqueIslands[k] == id)
                            {
                                dup = true;
                                break;
                            }
                        }
                        if (!dup)
                            uniqueIslands[count++] = id;
                    }
                    if (j < N - 1 && grid[i][j + 1] > 1)
                    {
                        int id = grid[i][j + 1];
                        bool dup = false;
                        for (int k = 0; k < count; ++k)
                        {
                            if (uniqueIslands[k] == id)
                            {
                                dup = true;
                                break;
                            }
                        }
                        if (!dup)
                            uniqueIslands[count++] = id;
                    }
                    int currArea = 1;
                    for (int k = 0; k < count; ++k)
                    {
                        currArea += islandSize[uniqueIslands[k]];
                    }
                    maxArea = std::max(maxArea, currArea);
                }
            }
        }
        return hasZero ? maxArea : N * N;
    }
};
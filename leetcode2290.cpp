// https://leetcode.cn/problems/minimum-obstacle-removal-to-reach-corner/
#include <vector>
#include <queue>
using std::vector;
using std::deque;

struct Point
{
    int x = 0, y = 0;
    Point(int x, int y): x(x), y(y) {}
};
class Solution
{
public:
    int minimumObstacles(vector<vector<int>> &grid)
    {
        const int M = grid.size(), N = grid[0].size();
        vector<vector<int>> distance(M, vector<int>(N, 1000000));
        deque<Point> q;
        distance[0][0] = 0;
        q.emplace_back(Point(0, 0));
        while (!q.empty())
        {
            Point efficient = q.front(); q.pop_front();
            int x = efficient.x, y = efficient.y;
            if (x == M-1 && y == N-1)
            {
                return distance[x][y];
            }
            if (x > 0)
            {
                if (distance[x][y] + grid[x-1][y] < distance[x-1][y])
                {
                    distance[x-1][y] = distance[x][y] + grid[x-1][y];
                    if (grid[x-1][y] == 0)
                    {
                        q.emplace_front(Point(x-1, y));
                    }
                    else
                    {
                        q.emplace_back(Point(x-1, y));
                    }
                }
            }
            if (x < M-1)
            {
                if (distance[x][y] + grid[x+1][y] < distance[x+1][y])
                {
                    distance[x+1][y] = distance[x][y] + grid[x+1][y];
                    if (grid[x+1][y] == 0)
                    {
                        q.emplace_front(Point(x+1, y));
                    }
                    else
                    {
                        q.emplace_back(Point(x+1, y));
                    }
                }
            }
            if (y > 0)
            {
                if (distance[x][y] + grid[x][y-1] < distance[x][y-1])
                {
                    distance[x][y-1] = distance[x][y] + grid[x][y-1];
                    if (grid[x][y-1] == 0)
                    {
                        q.emplace_front(Point(x, y-1));
                    }
                    else
                    {
                        q.emplace_back(Point(x, y-1));
                    }
                }
            }
            if (y < N-1)
            {
                if (distance[x][y] + grid[x][y+1] < distance[x][y+1])
                {
                    distance[x][y+1] = distance[x][y] + grid[x][y+1];
                    if (grid[x][y+1] == 0)
                    {
                        q.emplace_front(Point(x, y+1));
                    }
                    else
                    {
                        q.emplace_back(Point(x, y+1));
                    }
                }
            }
        }
        return 0;
    }
};
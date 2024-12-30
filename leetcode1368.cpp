// https://leetcode.cn/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid/
#include <vector>
#include <deque>
using std::vector;
using std::deque;

struct Point
{
    int x, y;
    Point(int x, int y): x(x), y(y) {}
};
class Solution {
public:
    int minCost(vector<vector<int>>& grid) {
        deque<Point> q;
        const int M = grid.size(), N = grid[0].size();
        vector<vector<int>> changes(M, vector<int>(N, 1000));
        q.emplace_back(Point(0, 0));
        changes[0][0] = 0;
        while (!q.empty())
        {
            Point efficient = q.front(); q.pop_front();
            int x = efficient.x, y = efficient.y;
            if (x == M-1 && y == N-1)
            {
                return changes[M-1][N-1];
            }
            if (x > 0)
            {
                int change = grid[x][y] != 4;
                if (change + changes[x][y] < changes[x-1][y])
                {
                    changes[x-1][y] = change + changes[x][y];
                    if (change == 0)
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
                int change = grid[x][y] != 3;
                if (change + changes[x][y] < changes[x+1][y])
                {
                    changes[x+1][y] = change + changes[x][y];
                    if (change == 0)
                    {
                        q.emplace_front(Point(x+1, y));
                    }
                    else
                    {
                        q.emplace_back(Point(x+1, y));
                    }
                } 
            }
            if (y < N-1)
            {
                int change = grid[x][y] != 1;
                if (change + changes[x][y] < changes[x][y+1])
                {
                    changes[x][y+1] = change + changes[x][y];
                    if (change == 0)
                    {
                        q.emplace_front(Point(x, y+1));
                    }
                    else
                    {
                        q.emplace_back(Point(x, y+1));
                    }
                } 
            }
            if (y > 0)
            {
                int change = grid[x][y] != 2;
                if (change + changes[x][y] < changes[x][y-1])
                {
                    changes[x][y-1] = change + changes[x][y];
                    if (change == 0)
                    {
                        q.emplace_front(Point(x, y-1));
                    }
                    else
                    {
                        q.emplace_back(Point(x, y-1));
                    }
                } 
            }
        }
        return -1;
    }
};
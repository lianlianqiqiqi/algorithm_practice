// https://leetcode.cn/problems/trapping-rain-water-ii/
#include<vector>
#include<queue>
using std::vector;
using std::priority_queue;
struct Point
{
    int x = 0, y = 0, w = 0;
    Point(int x, int y, int w): x(x), y(y), w(w) {}
    bool operator< (const Point& p) const
    {
        return w > p.w;
    } 
};

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        const int M = heightMap.size(), N = heightMap[0].size();
        vector<vector<bool>> visited(M, vector<bool>(N, false));
        priority_queue<Point> q;
        for (int i = 0; i < M; ++i)
        {
            visited[i][0] = true; visited[i][N-1] = true;
            q.emplace(Point(i, 0, heightMap[i][0]));
            q.emplace(Point(i, N-1, heightMap[i][N-1]));
        }
        for (int j = 0; j < N; ++j)
        {
            visited[0][j] = true; visited[M-1][j] = true;
            q.emplace(Point(0, j, heightMap[0][j]));
            q.emplace(Point(M-1, j, heightMap[M-1][j]));
        }
        int result = 0;
        while (!q.empty())
        {
            Point p = q.top(); q.pop();
            int x = p.x, y = p.y, w = p.w;
            if (x > 0 && !visited[x-1][y])
            {
                visited[x-1][y] = true;
                int bottleNeck = std::max(heightMap[x-1][y], w);
                q.emplace(Point(x-1, y, bottleNeck));
                result += bottleNeck-heightMap[x-1][y];
            }
            if (x < M-1 && !visited[x+1][y])
            {
                visited[x+1][y] = true;
                int bottleNeck = std::max(heightMap[x+1][y], w);
                q.emplace(Point(x+1, y, bottleNeck));
                result += bottleNeck - heightMap[x+1][y];
            }
            if (y > 0 && !visited[x][y-1])
            {
                visited[x][y-1] = true;
                int bottleNeck = std::max(heightMap[x][y-1], w);
                q.emplace(Point(x, y-1, bottleNeck));
                result += bottleNeck - heightMap[x][y-1];
            }
            if (y < N-1 && !visited[x][y+1])
            {
                visited[x][y+1] = true;
                int bottleNeck = std::max(heightMap[x][y+1], w);
                q.emplace(Point(x, y+1, bottleNeck));
                result += bottleNeck - heightMap[x][y+1];   
            }
        }
        return result;
    }
};
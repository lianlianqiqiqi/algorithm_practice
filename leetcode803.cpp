// https://leetcode.cn/problems/bricks-falling-when-hit/
#include<vector>
using std::vector;

class Solution {
private:
    int M=0, N=0;
    vector<vector<int>> grid;
    int dfs(int i, int j, vector<vector<int>>& grid) {
        if (i == -1 || i == M || j == -1 || j == N || grid[i][j] != 1) return 0;
        grid[i][j] = 2;
        return dfs(i-1, j, grid) + dfs(i+1, j, grid) + dfs(i, j-1, grid) + dfs(i, j+1, grid) + 1;
    }
public:
    vector<int> hitBricks(vector<vector<int>>& g, vector<vector<int>>& hits) {
        grid = std::move(g);
        M = grid.size(), N = grid[0].size();
        int hitSize = hits.size();

        vector<int> result(hitSize, 0);
        for (auto& hit: hits) {
            --grid[hit[0]][hit[1]];
        }
        for (int i = 0; i < N; ++i) {
            dfs(0, i, grid);
        }
        for (int i = hitSize-1; i >= 0; --i) {
            int x = hits[i][0], y = hits[i][1];
            grid[x][y]++;
            if (!grid[x][y]) {  result[i] = 0; continue; }
            if (x == 0 || (x > 0 && grid[x-1][y] == 2) || (x < M-1 && grid[x+1][y] == 2) || (y > 0 && grid[x][y-1] == 2) || (y < N-1 && grid[x][y+1] == 2)) {
                result[i] = dfs(x, y, grid) - 1;
            } else result[i] = 0;
        }
        return result;
    }
};
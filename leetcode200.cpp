// https://leetcode.cn/problems/number-of-islands/description/
#include <vector>
using std::vector;

class Solution {
private:
    int M, N;
    void spread(int i, int j, vector<vector<char>>& islands) {
        if (i < 0 || i >= M || j < 0 || j >= N || islands[i][j] != '1') return;
        islands[i][j] = '2';
        spread(i-1, j, islands);
        spread(i+1, j, islands);
        spread(i, j+1, islands);
        spread(i, j-1, islands);
    }
public:
    int numIslands(vector<vector<char>>& grid) {
        int islandNum = 0;
        M = grid.size(), N = grid[0].size();

        for (int i = 0; i < M;++i) {
            for (int j = 0; j < N; ++j) {
                if (grid[i][j] == '1') {
                    ++islandNum;
                    spread(i, j, grid);
                }
            }
        }
        return islandNum;
    }
};
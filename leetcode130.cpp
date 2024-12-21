// https://leetcode.cn/problems/surrounded-regions/
#include <vector>
using std::vector;

class Solution
{
private:
    int M = 0, N = 0;
    void dfs(int i, int j, vector<vector<char>> &board)
    {
        if (i < 0 || i >= M || j < 0 || j >= N || board[i][j] != 'O')
            return;
        board[i][j] = 'M';
        dfs(i - 1, j, board);
        dfs(i + 1, j, board);
        dfs(i, j - 1, board);
        dfs(i, j + 1, board);
    }

public:
    void solve(vector<vector<char>> &board)
    {
        M = board.size(), N = board[0].size();
        for (int j = 0; j < N; ++j)
        {
            dfs(0, j, board);
            dfs(M - 1, j, board);
        }
        for (int i = 0; i < M; ++i)
        {
            dfs(i, 0, board);
            dfs(i, N - 1, board);
        }
        for (int i = 0; i < M; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                if (board[i][j] == 'O')
                    board[i][j] = 'X';
                else if (board[i][j] == 'M')
                    board[i][j] = 'O';
            }
        }
    }
};
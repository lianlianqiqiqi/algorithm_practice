// https://leetcode.cn/problems/number-of-good-paths/

#include <vector>
#include <algorithm>
#include <unordered_set>
using std::vector;
using std::unordered_set;

class Solution {
private:
    int cnt = 0;
    int father[30005];
    int maxElementNum[30005];
    int find(int x) {
        if (x != father[x]) {
            father[x] = find(father[x]);
        }
        return father[x];
    }
public:
    int numberOfGoodPaths(vector<int>& vals, vector<vector<int>>& edges) {
        cnt = 0;
        const int N = vals.size();
        for (int i = 0; i < N; ++i) {
            father[i] = i;
            maxElementNum[i] = 1;
        }
        std::ranges::sort(edges, [&vals](const vector<int>& edge1, const vector<int>& edge2) {
            return std::max(vals[edge1[0]], vals[edge1[1]]) < std::max(vals[edge2[0]], vals[edge2[1]]); 
        });
        for (const vector<int>& edge: edges) {
            const int x = edge[0], y = edge[1];
            int xFather = find(x), yFather = find(y);
            if (vals[xFather] > vals[yFather]) {
                father[yFather] = xFather;
            } else if (vals[xFather] < vals[yFather]) {
                father[xFather] = yFather;
            } else {
                cnt += maxElementNum[xFather]*maxElementNum[yFather];
                maxElementNum[xFather] += maxElementNum[yFather];
                father[yFather] = xFather;
            }
        }
        return cnt + N;
    }
};
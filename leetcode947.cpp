#include <vector>
#include <numeric>
using std::vector;

class Solution {
private:
    int removedStone = 0;
    int xMap[10005] = {0}, yMap[10005] = {0};
    int find(int i, vector<int>& father) {
        return father[i] = father[i] == i ? i : find(father[i], father);
    }
    bool isSameSet(int i, int j, vector<int>& father) {
        return find(i,father) == find(j,father);
    }
    void unionn(int i, int j, vector<int>& father) {
        if (!isSameSet(i, j, father)) {
            father[find(j, father)] = find(i, father);
            removedStone++;
        }
    }
public:
    int removeStones(vector<vector<int>>& stones) {
        const int n = stones.size();
        vector<int> father(n);
        std::iota(father.begin(), father.end(), 0);
        removedStone = 0;
        for (int i = 0; i < n; ++i) {
            int x = stones[i][0], y = stones[i][1];
            if (xMap[x]) unionn(i, xMap[x]-1, father);
            else xMap[x] = i+1;

            if (yMap[y]) unionn(i, yMap[y]-1, father);
            else yMap[y] = i+1;
        }
        return removedStone;
    }
};

int main() {
    return 0;
}
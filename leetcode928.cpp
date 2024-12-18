// https://leetcode.cn/problems/minimize-malware-spread-ii/

#include<vector>
#include<algorithm>
using std::vector;

class Solution {
private:
    int find(int i, vector<int>& father) {
        return father[i] = father[i] == i ? i : find(father[i], father);
    }
    bool isSameSet(int i, int j, vector<int>& father) {
        return find(i,father) == find(j,father);
    }
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        const int N = graph.size(), M = initial.size();
        vector<bool> isInfected(N, false);
        vector<int> father(N, 0);
        vector<int> groupMember(N);
        vector<int> connected(N);
        vector<int> countAffected(N, 0);
        std::ranges::sort(initial);
        for (int node: initial) isInfected[node] = true;
        for (int i = 0; i < N; ++i) {
            father[i] = i;
            groupMember[i] = 1;
            connected[i] = i;
        }
        for (int i = 0; i < N; ++i) {
            if (isInfected[i]) continue;
            for (int j = 0; j < N; ++j) {
                if (!isInfected[j] && graph[i][j] && !isSameSet(i, j, father)) {
                    int iFather = find(i, father), jFather = find(j, father);
                    groupMember[iFather] += groupMember[jFather];
                    father[jFather] = iFather;
                }
            }
        }
        for (int i = 0; i < M; ++i) {
            int infectedNode = initial[i];
            for (int j = 0; j < N; ++j) {
                if (isInfected[j]) continue;
                int jRoot = find(j, father);
                if (graph[infectedNode][j] && connected[jRoot] != -1) {
                    if (connected[jRoot] != jRoot && connected[jRoot] != infectedNode) connected[jRoot] = -1;
                    else connected[jRoot] = infectedNode;
                }
            }
        }
        for (int i = 0; i < N; ++i) {
            if (!isInfected[i]) {
                int iRoot = find(i, father);
                if (i == iRoot) {
                    int connect = connected[iRoot];
                    if (connect != iRoot && connect != -1) {
                        countAffected[connect] += groupMember[iRoot];
                    }
                }
            }
        }
        int bestToRemove = initial[0];
        for (int i = 1; i < M; ++i) {
            if (countAffected[initial[i]] > countAffected[bestToRemove]) {
                bestToRemove = initial[i];
            }
        }
        return bestToRemove;
    }
};
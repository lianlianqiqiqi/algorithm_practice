// https://leetcode.cn/problems/find-all-people-with-secret/

#include<vector>
#include<algorithm>
using std::vector;

class Solution {
private:
    int find(int i, int* father) {
        return father[i] = father[i] == i ? i : find(father[i], father);
    }
    bool isSameSet(int i, int j, int* father) {
        return find(i, father) == find(j, father);
    }
    void unionn(int i, int j, int* father) {
        father[find(j, father)] = find(i, father);
    }
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        vector<int> result;
        int MEETINGS_NUM = meetings.size();
        meetings.emplace_back(std::vector<int>{0, 0, 100005});
        int* father = new int[n];
        for (int i = 0; i < n; ++i) father[i] = i;
        father[firstPerson] = 0;
        std::ranges::sort(meetings, [](vector<int>& a, vector<int>& b) {
            return a[2] < b[2];
        });
        for (int l = 0, r = 0; r < MEETINGS_NUM;) {
            while (r < MEETINGS_NUM && meetings[r+1][2] == meetings[l][2]) ++r;
            for (int i = l; i <= r; ++i) unionn(meetings[i][0], meetings[i][1], father);
            for (int i = l; i <= r; ++i) {
                int a = meetings[i][0], b = meetings[i][1];
                if (!isSameSet(0, a, father)) father[a] = a;
                if (!isSameSet(0, b, father)) father[b] = b;
            }
            l = ++r;
        }
        for (int i = 0; i < n; ++i) {
            if (isSameSet(0, i, father)) result.push_back(i);
        }
        return result;
    }
};
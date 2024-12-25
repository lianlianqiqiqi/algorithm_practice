// https://leetcode.cn/problems/maximum-employees-to-be-invited-to-a-meeting/
#include <vector>
using std::vector;

class Solution
{
private:
    int find(int i, vector<int> &father)
    {
        if (father[i] == i)
        {
            return i;
        }
        else
        {
            father[i] = find(father[i], father);
            return father[i];
        }
    }
    bool isSameSet(int i, int j, vector<int> &father)
    {
        int iFather = find(i, father);
        int jFather = find(j, father);
        return iFather == jFather;
    }
    void add(int i, int j, vector<int> &father)
    {
        int iFather = find(i, father);
        int jFather = find(j, father);
        father[jFather] = iFather;
    }

public:
    int maximumInvitations(vector<int> &favorite)
    {
        const int N = favorite.size();
        vector<int> father(N, 0);
        vector<int> setRepresentative;
        vector<bool> setSmallCircle;
        vector<int> inDegree(N, 0);
        vector<int> hang(N, 0);
        int total = 0;
        int circle = 0;
        for (int i = 0; i < N; ++i)
        {
            ++inDegree[favorite[i]];
            father[i] = i;
        }
        for (int i = 0; i < N; ++i)
        {
            // i与favorite[i]在一个集合里, 此时要形成环了 将此时的father作为setRepresentative
            if (isSameSet(i, favorite[i], father))
            {
                setRepresentative.push_back(find(i, father));
                if (favorite[favorite[i]] == i)
                {
                    setSmallCircle.push_back(true);
                }
                else
                {
                    setSmallCircle.push_back(false);
                }
            }
            else
            {
                add(favorite[i], i, father);
            }
        }
        const int M = setRepresentative.size();
        for (int i = 0; i < M; ++i)
        {
            const int representative = setRepresentative[i];
            vector<int> zeroIndegree;
            if (setSmallCircle[i])
            {
                for (int i = 0; i < N; ++i)
                {
                    if (isSameSet(representative, i, father) && inDegree[i] == 0)
                    {
                        zeroIndegree.push_back(i);
                    }
                }
                int left = 0;
                while (left < zeroIndegree.size())
                {
                    int currZero = zeroIndegree[left++];
                    int leftFavorite = favorite[currZero];
                    hang[leftFavorite] = std::max(hang[leftFavorite], hang[currZero] + 1);
                    if (--inDegree[leftFavorite] == 0)
                    {
                        zeroIndegree.push_back(leftFavorite);
                    }
                }
                total += hang[representative] + hang[favorite[representative]] + 2;
            }
            else
            {
                int setSize = 0;
                for (int i = 0; i < N; ++i)
                {
                    if (isSameSet(representative, i, father))
                    {
                        ++setSize;
                        if (inDegree[i] == 0)
                        {
                            zeroIndegree.push_back(i);
                        }
                    }
                }
                int left = 0;
                while (left < zeroIndegree.size())
                {
                    int currZero = zeroIndegree[left++];
                    int leftFavorite = favorite[currZero];
                    if (--inDegree[leftFavorite] == 0)
                    {
                        zeroIndegree.push_back(leftFavorite);
                    }
                }
                circle = std::max(circle, setSize-(int)zeroIndegree.size());
            }
        }
        return std::max(total, circle);
    }
};
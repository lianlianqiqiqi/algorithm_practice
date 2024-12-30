// https://leetcode.cn/problems/word-ladder-ii/
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using std::string;
using std::vector;
using std::deque;
using std::unordered_set;
using std::unordered_map;
class Solution
{
private:
    vector<vector<string>> result;
    vector<vector<int>> from;
    vector<string> path;
    vector<string> wordList;
    void backtrack(int currIdx, int endIdx)
    {
        if (currIdx == endIdx)
        {
            result.push_back(path);
            return;
        }
        for (int next: from[currIdx])
        {
            path.push_back(wordList[next]);
            backtrack(next, endIdx);
            path.pop_back();
        }
    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &w)
    {
        wordList = std::move(w);
        const int N = wordList.size(), wordLen = beginWord.size();
        vector<vector<int>> graph(N);
        unordered_map<string, int> strToIdx;
        unordered_set<int> layerNew;
        from = vector<vector<int>>(N+1);
        deque<int> q;
        vector<bool> visited(N, false);
        path = vector<string>{beginWord};
        result = vector<vector<string>>();
        for (int i = 0; i < N; ++i)
        {
            strToIdx[wordList[i]] = i;
        }
        if (!strToIdx.contains(endWord))
        {
            return {};
        }
        for (int i = 0; i < N; ++i)
        {
            string currStr = wordList[i];
            for (int j = 0; j < wordLen; ++j)
            {
                char ch = wordList[i][j];
                for (int k = 'a'; k <= 'z'; ++k)
                {
                    if (ch != k)
                    {
                        currStr[j] = k;
                        if (strToIdx.contains(currStr))
                        {
                            graph[i].push_back(strToIdx[currStr]);
                        }
                    }
                }
                currStr[j] = ch;
            }
        }
        string tempStr = beginWord;
        for (int j = 0; j < wordLen; ++j)
        {
            char ch = beginWord[j];
            for (int k = 'a'; k <= 'z'; ++k)
            {
                if (ch != k)
                {
                    tempStr[j] = k;
                    if (strToIdx.contains(tempStr))
                    {
                        graph[strToIdx[tempStr]].push_back(N);
                    }
                }
            }
            tempStr[j] = ch;
        }
        int endIdx = strToIdx[endWord];
        visited[endIdx] = true;
        q.push_back(endIdx);
        while (!q.empty())
        {
            int sz = q.size();
            layerNew.clear();
            bool shouldReturn = false;
            for (int i = 0; i < sz; ++i)
            {
                int curr = q.front(); q.pop_front();
                for (int adjacent: graph[curr])
                {
                    if (!visited[adjacent])
                    {
                        from[adjacent].push_back(curr);
                        if (!layerNew.contains(adjacent))
                        {
                            layerNew.insert(adjacent);
                            q.push_back(adjacent);
                        }
                    }
                }
            }
            for (int layerVisited: layerNew)
            {
                visited[layerVisited] = true;
                if (layerVisited == N)
                {
                    shouldReturn = true;
                }
            }
            if (shouldReturn)
            {
                backtrack(N, endIdx);
                return result;
            }
        }
        return {};
    }
};
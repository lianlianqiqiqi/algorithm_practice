// https://leetcode.cn/problems/word-ladder/
#include <vector>
#include <queue>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
using std::vector;
using std::string;
using std::deque;
using std::unordered_map;
using std::unordered_set;

class Solution {
public:
    int ladderLength(string& beginWord, string& endWord, vector<string>& wordList) {
        const int N = wordList.size(), wordLen = beginWord.size();
        vector<vector<int>> graph(N+1);
        unordered_map<string, int> strToIdx;
        vector<bool> visited(N+1);
        for (int i = 0; i < N; ++i)
        {
            strToIdx[wordList[i]] = i;
        }
        if (!strToIdx.contains(endWord))
        {
            return 0;
        }
        if (strToIdx.contains(beginWord))
        {
            visited[strToIdx[beginWord]] = true;
        }
        wordList.push_back(beginWord);
        strToIdx[beginWord] = N;
        for (int i = 0; i <= N; ++i)
        {
            string tempStr = wordList[i];
            for (int pos = 0; pos < wordLen; ++pos)
            {
                char ch = wordList[i][pos];
                for (char changedCh = 'a'; changedCh <= 'z'; ++changedCh)
                {
                    if (changedCh != ch)
                    {
                        tempStr[pos] = changedCh;
                        if (strToIdx.contains(tempStr))
                        {
                            graph[i].push_back(strToIdx[tempStr]);
                        }
                    }
                }
                tempStr[pos] = ch;
            }
        }
        int endPos = strToIdx[endWord], beginPos = strToIdx[beginWord];
        deque<int> beginSide, endSide;
        unordered_set<int> beginLayer, endLayer;
        for (int point: graph[endPos])
        {
            if (point == beginPos) return 2;
            endLayer.insert(point);
            visited[point] = true;
            endSide.push_back(point);
        }
        for (int point: graph[beginPos])
        {
            if (endLayer.contains(point)) return 3;
            beginLayer.insert(point);
            visited[point] = true;
            beginSide.push_back(point);
        }
        int level = 2;
        while (!beginSide.empty() && !endSide.empty())
        {
            ++level;
            unordered_set<int>& smallerLayer = beginLayer.size()>endLayer.size()?endLayer:beginLayer;
            deque<int>& smallerOne = beginLayer.size()>endLayer.size()?endSide:beginSide;
            unordered_set<int>& biggerLayer = beginLayer.size()>endLayer.size()?beginLayer:endLayer;
            int sz = smallerOne.size();
            smallerLayer.clear();
            for (int i = 0; i < sz; ++i)
            {
                int curr = smallerOne.front(); smallerOne.pop_front();
                for (int point: graph[curr])
                {
                    if (biggerLayer.contains(point)) return level+1;
                    if (!visited[point])
                    {
                        visited[point] = true;
                        smallerLayer.insert(point);
                        smallerOne.push_back(point);
                    }
                }
            }
        }
        return 0;
    }
};
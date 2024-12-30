// https://leetcode.cn/problems/stickers-to-spell-word/
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <deque>
#include <unordered_set>
using std::string;
using std::vector;
using std::deque;
using std::unordered_set;
class Solution
{
public:
    int minStickers(vector<string> &stickers, string &target)
    {
        std::sort(target.begin(), target.end());
        const int N = static_cast<int>(stickers.size());
        deque<string> queue;
        vector<vector<int>> graph(26);
        unordered_set<string> s;
        for (int i = 0; i < N; ++i)
        {
            std::sort(stickers[i].begin(), stickers[i].end());
            string &sticker = stickers[i];
            graph[sticker[0] - 'a'].push_back(i);
            for (int j = 1; j < (int)sticker.size(); ++j)
            {
                if (sticker[j] != sticker[j - 1])
                {
                    graph[sticker[j] - 'a'].push_back(i);
                }
            }
        }
        queue.push_back(target);
        s.insert(target);
        int level = 0;
        while (!queue.empty())
        {
            ++level;
            int sz = queue.size();
            for (int idx = 0; idx < sz; ++idx)
            {
                const string remaining = queue.front(); queue.pop_front();
                s.erase(remaining);
                vector<int> &reachable = graph[remaining[0] - 'a'];
                for (int adj : reachable)
                {
                    const string &sticker = stickers[adj];
                    std::ostringstream os;
                    int i_rem = 0, i_stk = 0;
                    int remSz = (int)remaining.size(), stkSz = (int)sticker.size();
                    while (i_rem < remSz && i_stk < stkSz)
                    {
                        while (i_stk < stkSz && sticker[i_stk] < remaining[i_rem])
                        {
                            ++i_stk;
                        }
                        if (i_stk == stkSz) break;
                        if (sticker[i_stk] == remaining[i_rem])
                        {
                            ++i_rem;
                            ++i_stk;
                        }
                        else
                        {
                            os << remaining[i_rem++];
                        }
                    }
                    while (i_rem < remSz)
                    {
                        os << remaining[i_rem++];
                    }
                    string newRem = os.str();
                    
                    if (newRem.empty())
                    {
                        return level;
                    }
                    if (!s.contains(newRem))
                    {
                        queue.push_back(newRem);
                        s.insert(newRem);
                    }
                }
            }
        }
        return -1;
    }
};
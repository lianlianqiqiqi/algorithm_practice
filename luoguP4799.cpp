// https://www.luogu.com.cn/problem/P4799
#include<cstdio>
#include<vector>
#include<algorithm>
using std::vector;

void dfs(unsigned long long amount, int curr, int end, vector<unsigned long long>& prices, vector<unsigned long long>& money)
{
    if (curr > end)
    {
        money.push_back(amount);
        return;
    }
    dfs(amount+prices[curr], curr + 1, end, prices, money);
    dfs(amount, curr + 1, end, prices, money);
}

int main()
{
    int N;
    unsigned long long M;
    scanf("%d %llu", &N, &M);
    vector<unsigned long long> prices(N);
    vector<unsigned long long> moneyGroup1;
    vector<unsigned long long> moneyGroup2;
    for (int i = 0; i < N; ++i)
    {
        scanf("%llu", &prices[i]);
    }
    int firstGroupEnd = N / 2;
    int secondGroupStart = firstGroupEnd + 1;
    dfs(0, 0, firstGroupEnd, prices, moneyGroup1);
    dfs(0, secondGroupStart, N-1, prices, moneyGroup2);
    std::sort(moneyGroup1.begin(), moneyGroup1.end());
    std::sort(moneyGroup2.begin(), moneyGroup2.end());
    const int n1 = moneyGroup1.size(), n2 = moneyGroup2.size();
    unsigned long long result = 0;
    for (int l = 0, r = n2-1; l < n1 && r >= 0; ++l)
    {
        while (r >= 0 && moneyGroup1[l] + moneyGroup2[r] > M)
        {
            r--;
        }
        if (r >= 0)
        {
            result += r + 1;
        }
    }
    printf("%llu\n", result);
    return 0;
}
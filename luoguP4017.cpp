// https://www.luogu.com.cn/problem/P4017
#include<cstdio>
#include<cstring>

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    int result = 0;
    int* to = new int[M+1];
    int* next = new int[M+1];
    int* count = new int[N+1];
    int* head = new int[N+1];
    int* inDegree = new int[N+1];
    int cnt = 1;
    memset(head, 0, (N+1)*sizeof(int));
    memset(inDegree, 0, (N+1)*sizeof(int));
    memset(count, 0, (N+1)*sizeof(int));

    for (int i = 1; i <= M; ++i)
    {
        int f, t;
        scanf("%d %d", &f, &t);
        to[cnt] = t;
        next[cnt] = head[f];
        head[f] = cnt++;
        ++inDegree[t];
    }

    int* processed = new int[N];
    int sz = 0, curr = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (inDegree[i] == 0)
        {
            count[i] = 1;
            processed[sz++] = i;
        }
    }
    while (curr < N)
    {
        int findNext = processed[curr++];
        int idx = head[findNext];
        if (idx == 0)
        {
            result = (result + count[findNext]) % 80112002;
            continue;
        }
        while (idx != 0)
        {
            int t = to[idx];
            --inDegree[t];
            count[t] = (count[t] + count[findNext]) % 80112002;
            idx = next[idx];
            if (inDegree[t] == 0)
            {
                processed[sz++] = t;
            }
        }
    }
    printf("%d\n", result);
}
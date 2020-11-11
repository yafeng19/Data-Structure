class Solution
{
    // 将满足完全平方数条件的两个点连接成一条边，回溯dfs计算哈密顿路径数量；
    map<int, int> count;         // 存储每个结点值数量
    map<int, vector<int>> graph; /** 存储邻接表，这里把每个结点本身都存进去作为一条
                                    虚拟边，如果该结点值有多个该边存在，如果唯一，
                                    该虚拟边不存在，在遍历邻接表的时候，每次遍历开始
                                    将count[x]--，这样遍历下一条边的时候可以通过count[x] != 0,来过滤掉唯一结点的虚拟边。
                                **/
public:
    int dfs(int x, int todo)
    {                // x是当前结点，todo是需要深度优先搜素的结点数
        count[x]--;  // 访问x结点
        int ans = 1; // 尾结点直接返回 1
        if (todo != 0)
        {
            ans = 0; // 非尾结点归0，然后统计每个分支的哈密顿路径数
            for (auto &t : graph[x])
                if (count[t] != 0) // 过滤唯一结点
                    ans += dfs(t, todo - 1);
        }
        count[x]++; // 恢复x结点
        return ans; // 尾结点就返回1 非尾结点就返回归零后统计的ans数量
    }
    int numSquarefulPerms(vector<int> &A)
    {
        // 利用map存储然后遍历，可以巧妙避免对重复元素在同一深度的多次访问
        int N = A.size();
        /** 初始化count 和 graph **/
        for (auto &i : A)
            count[i]++; //对结点数量进行计数
        for (auto &p : count)
            for (auto &q : count)
            {
                int sqrt_pq = sqrt(p.first + q.first);
                if (p.first + q.first == sqrt_pq * sqrt_pq)
                    graph[p.first].push_back(q.first); // 若构成完全平方数则记录
            }
        /** dfs计算哈密顿路径数量 **/
        int ans = 0;
        for (auto &c : count)
            ans += dfs(c.first, N - 1);
        return ans;
    }
};

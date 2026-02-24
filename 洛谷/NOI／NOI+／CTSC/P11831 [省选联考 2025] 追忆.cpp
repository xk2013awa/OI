// Problem: P11831 [省选联考 2025] 追忆
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P11831
// Memory Limit: 2048 MB
// Time Limit: 9000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

#include <algorithm>
#include <bitset>
#include <cstdio>
#include <queue>
#include <vector>

constexpr int N = 1e5 + 5, BUF = 1 << 20;

struct Node
{
	int u, a, b;
	
	bool operator >(const Node& rks) const;
};

inline int read(void);
inline void write(int x);
void dfs(int u);

int c, T, n, m, q, u, v, l, r, st, op, d[N], pos[N], topo[N];
bool vis[N];
char *p1, *p2, *p3, buf[BUF], obuf[BUF];
std::bitset<N> cnt[N];
std::vector<int> G[N];
std::queue<int> queue;
Node node[N];

#define getchar() (p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUF, stdin), p1 == p2) ? EOF : *p1++)
#define putchar(x) (p3 - obuf < BUF) ? (*p3++ = x) : (fwrite(obuf, 1, BUF, stdout), p3 = obuf, *p3++ = x)

int main(void)
{
	c = read(), T = read();
	p3 = obuf;
	
	while (T--)
	{
		st = n = read();
		m = read();
		q = read();
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++)
		{
			d[i] = pos[i] = topo[i] = 0;
			vis[i] = false;
			cnt[i].reset();
			G[i].clear();
		}
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= m; i++)
		{
			u = read();
			v = read();
			G[u].push_back(v);
			d[v]++;
		}
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++) node[i].a = read();
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++) node[i].b = read();
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++) node[i].u = i;
		
		std::sort(node + 1, node + 1 + n, std::greater<Node>());
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++) pos[node[i].u] = i;
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++) if (d[i] == 0) queue.push(i);
		
		#pragma GCC unroll(32)
		while (!queue.empty())
		{
			int u = queue.front();
			queue.pop();
			topo[st--] = u;
			
			#pragma GCC unroll(32)
			for (int v : G[u]) if (--d[v] == 0) queue.push(v);
		}
		
		#pragma GCC unroll(32)
		for (int i = 1; i <= n; i++) if (!vis[topo[i]]) dfs(topo[i]);
		
		#pragma GCC unroll(32)
		while (q--)
		{
			op = read();
			
			if (op == 1)
			{
				u = read();
				v = read();
				std::swap(node[pos[u]].a, node[pos[v]].a);
			}
			else if (op == 2)
			{
				u = read();
				v = read();
				std::swap(node[pos[u]].b, node[pos[v]].b);
				std::swap(node[pos[u]], node[pos[v]]);
				std::swap(pos[u], pos[v]);
			}
			else if (op == 3)
			{
				u = read();
				l = read();
				r = read();
				
				if (!cnt[u].any())
				{
					write(0);
					continue;
				}
				
				bool flag = true;
				
				#pragma GCC unroll(32)
				for (int i = 1; i <= n; i++)
				{
					if (cnt[u][node[i].u] && l <= node[i].a && node[i].a <= r)
					{
						flag = false;
						write(node[i].b);
						break;
					}
				}
				
				if (flag) write(0);
				
				putchar('\n');
			}
		}
	}
	
	fwrite(obuf, 1, p3 - obuf, stdout);
	
	#define _ 0
	return ~~(0^_^0);
	#undef _
}

bool Node::operator >(const Node& rks) const
{
	if (this->b == rks.b) return this->a < rks.a;
	return this->b > rks.b;
}

inline int read(void)
{
    int x = 0;
    char ch = getchar();
    
    while (ch < '0' || ch > '9') ch = getchar();
    
    while (ch >= '0' && ch <= '9')
    {
    	x = (x << 1) + (x << 3) + (ch ^ '0');
    	ch = getchar();
    }
    
   	return x;
}

inline void write(int x)
{
    if (x > 9) write(x / 10);
        
    putchar((x % 10) ^ '0');
}

void dfs(int u)
{
	vis[u] = true;
	cnt[u].set(u);
	
	for (int v : G[u])
	{
		if (!vis[v]) dfs(v);
		cnt[u] |= cnt[v];
	}
}

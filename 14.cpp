#include <cstdio>
#include <cstring>
#include <algorithm>

struct node
{
	int x, y, z;
	int cas, pos;
};

int n, m;
int last;
node v[4000005], tmp[4000005];
int times;
int in[500005], out[500005];
int maxx;
int bit[500055];
int knum;
int ch[500005][26];
int ans[500005];
int top[5];
int t[5][500005];
int xx[500005], yy[500005], zz[500005];
char x[500005], y[500005], z[500005];

bool comp(node x, node y)
{
	return x.x < y.x || (x.x == y.x && (x.cas == 0 ? 0 : 1) < (y.cas == 0 ? 0 : 1));
}

int insert(int u, char *s)
{
	int n = strlen(s + 1);
	for (int i = 1; i <= n; i++)
	{
		if (! ch[u][s[i] - 'a'])
		{
			knum++;
			ch[u][s[i] - 'a'] = knum;
		}
		u = ch[u][s[i] - 'a'];
	}
	return u;
}

void dfs(int u)
{
	times++;
	in[u] = times;
	for (int i = 0; i < 26; i++)
	{
		if (ch[u][i])
		{
			dfs(ch[u][i]);
		}
	}
	out[u] = times;
}

int lowbit(int x)
{
	return x & -x;
}

void add(int x, int delta)
{
	for (int i = x; i <= maxx; i += lowbit(i))
	{
		bit[i] += delta;
	}
}

int query(int x)
{
	int ans = 0;
	for (int i = x; i; i -= lowbit(i))
	{
		ans += bit[i];
	}
	return ans;
}

void solve(int l, int r)
{
	if (l == r)
	{
		return;
	}
	int mid = (l + r) >> 1;
	solve(l, mid);
	solve(mid + 1, r);
	int nowl = l;
	int nowr = mid + 1;
	while (nowl <= mid && nowr <= r)
	{
		if (v[nowl].y <= v[nowr].y)
		{
			if (v[nowl].cas == 0)
			{
				add(v[nowl].z, 1);
			}
			nowl++;
		}
		else
		{
			if (v[nowr].cas != 0)
			{
				ans[v[nowr].pos] += v[nowr].cas * query(v[nowr].z);
			}
			nowr++;
		}
	}
	while (nowl <= mid)
	{
		if (v[nowl].cas == 0)
		{
			add(v[nowl].z, 1);
		}
		nowl++;
	}
	while (nowr <= r)
	{
		if (v[nowr].cas != 0)
		{
			ans[v[nowr].pos] += v[nowr].cas * query(v[nowr].z);
		}
		nowr++;
	}
	for (int i = l; i <= mid; i++)
	{
		if (v[i].cas == 0)
		{
			add(v[i].z, -1);
		}
	}
	nowl = l;
	nowr = mid + 1;
	int tmplast = l - 1;
	while (nowl <= mid && nowr <= r)
	{
		if (v[nowl].y <= v[nowr].y)
		{
			tmplast++;
			tmp[tmplast] = v[nowl];
			nowl++;
		}
		else
		{
			tmplast++;
			tmp[tmplast] = v[nowr];
			nowr++;
		}
	}
	while (nowl <= mid)
	{
		tmplast++;
		tmp[tmplast] = v[nowl];
		nowl++;
	}
	while (nowr <= r)
	{
		tmplast++;
		tmp[tmplast] = v[nowr];
		nowr++;
	}
	for (int i = l; i <= r; i++)
	{
		v[i] = tmp[i];
	}
}

int main()
{
	knum = 3;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s%s%s", x + 1, y + 1, z + 1);
		xx[i] = insert(1, x);
		yy[i] = insert(2, y);
		zz[i] = insert(3, z);
	}
	times = 0;
	dfs(1);
	times = 0;
	dfs(2);
	times = 0;
	dfs(3);
	maxx = times + 10;
	last = 0;
	for (int i = 1; i <= n; i++)
	{
		last++;
		v[last].x = in[xx[i]];
		v[last].y = in[yy[i]];
		v[last].z = in[zz[i]];
		v[last].cas = 0;
	}
	top[1] = top[2] = top[3] = 1;
	t[1][1] = 1;
	t[2][1] = 2;
	t[3][1] = 3;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++)
	{
		char cas[3];
		scanf("%s", cas + 1);
		if (cas[1] == '+')
		{
			int pos;
			char c[3];
			scanf("%d%s", &pos, c + 1);
			top[pos]++;
			t[pos][top[pos]] = ch[t[pos][top[pos] - 1]][c[1] - 'a'];
			if (! t[1][top[1]] || ! t[2][top[2]] || ! t[3][top[3]])
			{
				ans[i] = 0;
			}
			else
			{
				int x = t[1][top[1]];
				int y = t[2][top[2]];
				int z = t[3][top[3]];
				last++;
				v[last].x = out[x];
				v[last].y = out[y];
				v[last].z = out[z];
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = out[y];
				v[last].z = out[z];
				v[last].cas = -1;
				v[last].pos = i;
				last++;
				v[last].x = out[x];
				v[last].y = in[y] - 1;
				v[last].z = out[z];
				v[last].cas = -1;
				v[last].pos = i;
				last++;
				v[last].x = out[x];
				v[last].y = out[y];
				v[last].z = in[z] - 1;
				v[last].cas = -1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = in[y] - 1;
				v[last].z = out[z];
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = out[y];
				v[last].z = in[z] - 1;
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = out[x];
				v[last].y = in[y] - 1;
				v[last].z = in[z] - 1;
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = in[y] - 1;
				v[last].z = in[z] - 1;
				v[last].cas = -1;
				v[last].pos = i;
			}
		}
		else
		{
			int pos;
			scanf("%d", &pos);
			top[pos]--;
			if (! t[1][top[1]] || ! t[2][top[2]] || ! t[3][top[3]])
			{
				ans[i] = 0;
			}
			else
			{
				int x = t[1][top[1]];
				int y = t[2][top[2]];
				int z = t[3][top[3]];
				last++;
				v[last].x = out[x];
				v[last].y = out[y];
				v[last].z = out[z];
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = out[y];
				v[last].z = out[z];
				v[last].cas = -1;
				v[last].pos = i;
				last++;
				v[last].x = out[x];
				v[last].y = in[y] - 1;
				v[last].z = out[z];
				v[last].cas = -1;
				v[last].pos = i;
				last++;
				v[last].x = out[x];
				v[last].y = out[y];
				v[last].z = in[z] - 1;
				v[last].cas = -1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = in[y] - 1;
				v[last].z = out[z];
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = out[y];
				v[last].z = in[z] - 1;
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = out[x];
				v[last].y = in[y] - 1;
				v[last].z = in[z] - 1;
				v[last].cas = 1;
				v[last].pos = i;
				last++;
				v[last].x = in[x] - 1;
				v[last].y = in[y] - 1;
				v[last].z = in[z] - 1;
				v[last].cas = -1;
				v[last].pos = i;
			}
		}
	}
	std::sort(v + 1, v + last + 1, comp);
	/*for (int i = 1; i <= last; i++)
	{
		printf("%d %d %d %d\n", v[i].cas, v[i].x, v[i].y, v[i].z);
	}*/
	solve(1, last);
	for (int i = 1; i <= m; i++)
	{
		printf("%d\n", ans[i]);
	}
	return 0;
}

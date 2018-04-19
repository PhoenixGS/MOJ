#include <cstdio>

void dfs(int pos, long long cas)
{
	vis[pos] = 1;
	maxmatch[pos] = 0;
	for (int i = 0; i < (1 << n); i++)
	{
		if (cas & (1 << i))
		{
			maxmatch[pos] = std::max(maxmatch[pos], bitcount[i]);
		}
	}
	for (int i = 0; i < (1 << n); i++)
	{
		long long newcas = cas;
		for (int j = 1; j <= n; j++)
		{
			if (i & (1 << (j - 1)))
			{
				for (int k = 0; k < (1 << n); k++)
				{
					if (cas & (1 << k))
					{
						newcas = newcas | (1ll << (k | (1 << (j - 1))));
					}
				}
			}
		}
		int newpos = map[newcas];
		if (! vis[newpos])
		{
			dfs(newpos, newcas);
		}
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	bitcount[0] = 0;
	for (int i = 1; i < (1 << n); i++)
	{
		bitcount[i] = bitcount[i >> 1] + (i & 1);
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			scanf("%lf", &x[i][j]);
		}
	}
	for (int i = 1; i <= m; i++)
	{
		for (int j = 0; j < (1 << n); j++)
		{
			xx[i][j] = 1.0;
			for (int k = 1; k <= n; k++)
			{
				if (j & (1 << (k - 1)))
				{
					xx[i][j] = xx[i][j] * x[i][k];
				}
				else
				{
					xx[i][j] = xx[i][j] * (1.0 - x[i][k]);
				}
			}
		}
	}
	knum = 1;
	map[1] = 1;
	dfs(1, 1);
}

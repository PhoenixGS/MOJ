#include <cstdio>
#include <map>

int n, m;
double x[10][2000];
int maxmatch[1000];
std::map<long long, int> map;
int trans[1000][100];
double f[2000][1000];
int bitcount[100];
double xx[2000][100];
double ans;
int knum;

void dfs(int pos, long long cas)
{
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
					if (cas & (1ll << k))
					{
						newcas = newcas | (1ll << (k | (1 << (j - 1))));
					}
				}
			}
		}
		int newpos = map[newcas];
		if (! newpos)
		{
			knum++;
			map[newcas] = knum;
			newpos = knum;
			dfs(newpos, newcas);
		}
		else
		{
			newpos = map[newcas];
		}
		trans[pos][i] = newpos;
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
	f[0][1] = 1.0;
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= knum; j++)
		{
			for (int k = 0; k < (1 << n); k++)
			{
				f[i][trans[j][k]] += f[i - 1][j] * xx[i][k];
			}
		}
	}
	ans = 0.0;
	for (int i = 1; i <= knum; i++)
	{
		ans = ans + f[m][i] * maxmatch[i];
	}
	printf("%.6f\n", ans);
	return 0;
}

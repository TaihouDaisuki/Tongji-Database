#include<iostream>
#include<string>
#include<cstring>

#define For(i,l,r) for(int i=l; i<=r; ++i)

using namespace std;

const int n = 5;
const int m = 8;
const int map[6][6] = { {0,0,0,0,0,0},
						{0,0,1,1,0,1},
						{0,1,0,1,0,1},
						{0,1,1,0,1,1},
						{0,0,0,1,0,1},
						{0,1,1,1,1,0} };
int flag[6][6];

void dfs(const int k, const int u, string ans)
{
	if (k == m)
	{
		cout << ans << endl;
		return;
	}
	For(v, 1, n) if (map[u][v] && !flag[u][v])
	{
		flag[u][v] = flag[v][u] = 1;
		dfs(k + 1, v, ans + char(v + '0'));
		flag[u][v] = flag[v][u] = 0;
	}
}
int main()
{
	string ans="1";
	For(i, 1, n) For(j, 1, n)
		flag[i][j] = 0;
	dfs(0, 1, ans);
	//system("pause");
	return 0;
}

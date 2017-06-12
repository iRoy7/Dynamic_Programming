/* Find minimum number of trials in worst cases */

#include <stdio.h>
const int SN = 101;
const int IMAX = 2147483647;
inline int max(int a, int b) { return (a > b) ? a : b; }

int N, K;

int dropEggs()
{
	int DT[SN][SN]; // Dynamic Table

	for (int e = 1; e <= N; e++)
		DT[e][1] = DT[e][0] = 1;
	for (int f = 1; f <= K; f++)
		DT[1][f] = f;

	for (int e = 2; e <= N; e++)
		for (int f = 2; f <= K; f++)
		{
			DT[e][f] = IMAX;
			for (int x = 1; x <= f; x++)
			{
				int res = 1 + max(DT[e - 1][x - 1], DT[e][f - x]);
				if (res < DT[e][f])
					DT[e][f] = res;
			}
		}

	return DT[N][K];
}

int main()
{
	int T; scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		scanf("%d %d", &N, &K);
		printf("\n Minimum number of trials in worst cases \
			   			   			   with %d eggs %d floors is %d\n", N, K, dropEggs());
	}

	return 0;
}
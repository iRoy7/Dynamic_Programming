/* Count all possible grid move path with all methods */

#include <stdio.h>
const int MAX = 110;
int DT[MAX][MAX];	// Dynamic Table
int N, M;			// N x M Grid

void cleanDT()
{
	for (int i = 0; i < MAX*MAX; i++)
		*((int *)DT + i) = 0;
}

bool canGo(int a, int b)
{
	return (!b || (double)N / M <= (double)a / b);
}

// Brute force with Recursion
int BF(int a, int b)
{
	if (a > N || b > M || !canGo(a, b)) return 0;
	if (a == N && b == M) return 1;
	return BF(a + 1, b) + BF(a, b + 1);
}

// Using Memo: DP: Bottom Up
// DT[a][b] = from (0, 0) to (a, b), get values from (a, b) to (0, 0)
// DT[a][b] = DT[a+1][b] + DT[a][b+1];
// Base cases:
// 1) DT[a][b] = 1 (a = N, b = M)
// 2) DT[a][b] = 0 (a/b < N/M)
int DP1(int a, int b)
{
	if (DT[a][b] == 0)
	{
		if (a > N || b > M || !canGo(a, b)) DT[a][b] = 0;
		else if (a == N && b == M) DT[a][b] = 1;
		else DT[a][b] = DP1(a + 1, b) + DP1(a, b + 1);
	}

	return DT[a][b];
}

// Using Memo: DP: Top Down
// DT[a][b] = from (a, b) to (0, 0), get values from (0, 0) to (a, b)
// DT[a][b] = DT[a-1][b] + DT[a][b-1];
// Base cases:
// 1) DT[a][b] = 1 (a = 0, b = 0)
// 2) DT[a][b] = 0 (a/b < N/M)
int DP2(int a, int b)
{
	if (DT[a][b] == 0)
	{
		if (a > N || b > M || !canGo(a, b)) DT[a][b] = 0;
		else if (a == 0 && b == 0) DT[a][b] = 1;
		else DT[a][b] = DP2(a - 1, b) + DP2(a, b - 1);
	}

	return DT[a][b];
}

int main()
{
	scanf("%d %d", &N, &M);

	// (1) Brute force with Rcursion
	printf("(1) Brute force: %d\n", BF(0, 0));

	// (2) DP(Bottom UP): Recursion + Memo
	cleanDT();
	printf("(2) DP(Bottom UP): Recursion+Memo: %d\n", DP1(0, 0));

	// (3) DP(Bottom Up): Iterative
	cleanDT();
	for (int i = 0; i <= N; i++)
		for (int j = 0; j <= M; j++)
		{
			if (i == 0 && j == 0) DT[i][j] = 1;
			else if (!canGo(i, j)) DT[i][j] = 0;
			else DT[i][j] = DT[i - 1][j] + DT[i][j - 1];
		}
	printf("(3) DP(Bottom Up): Iterative: %d\n", DT[N][M]);

	// (4) DP(Top Down): Recursion + Memo
	cleanDT();
	printf("(4) DP(Top Down): Recursion+Memo: %d\n", DP2(N, M));

	return 0;
}

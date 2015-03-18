#include <cstdio>
#include <cstring>

#define MAXN 10000

int n;
int h[3][MAXN];
int p[3];

void printChar(char c, int width)
{
	for (int i = 0; i < width; ++i)
	{
		putchar(c);
	}
}

void printLine(int width)
{
	if (width == -1)
	{
		printChar(' ', n - 1);
		putchar('|');
		printChar(' ', n - 1);
	}
	else
	{
		printChar(' ', n - width - 1);
		printChar('-', width * 2 + 1);
		printChar(' ', n - width - 1);
	}
}

void printHanoi()
{
	for (int i = n - 1; i >= 0; --i)
	{
		for (int j = 0; j < 3; ++j)
		{
			printf(" ");
			if (p[j] <= i)
			{
				printLine(-1);
			}
			else
			{
				printLine(h[j][i] - 1);
			}
		}
		putchar('\n');
	}
	for (int j = 0; j < 3; ++j)
	{
		printChar(' ', n - 1);
		if (n == 1)
		{
			putchar(' ');
			putchar(j + 'A');
		}
		else
		{
			putchar('-');
			putchar(j + 'A');
			putchar('-');
		}
		printChar(' ', n - 2);
	}
	putchar('\n');
	putchar('\n');
}

void move(int from, int to)
{
	char output[100];
	sprintf(output, "Move %d from %c to %c", h[to][p[to]++] = h[from][--p[from]], from + 'A', to + 'A');
	int l = n * 6 - strlen(output);
	printChar('-', l / 2);
	printf("%s", output);
	printChar('-', l - l / 2);
	putchar('\n');
	putchar('\n');
	printHanoi();
}

void solve(int x, char A, char B, char C)
{
	if (x == 1)
	{
		move(A, C);
	}
	else
	{
		solve(x - 1, A, C, B);
		move(A, C);
		solve(x - 1, B, A, C);
	}
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		h[0][i] = n - i;
	}
	p[0] = n;
	p[1] = 0;
	p[2] = 0;
	printHanoi();
	solve(n, 0, 1, 2);
	printChar('-', n * 3 - 3);
	printf("FINISH");
	printChar('-', n * 3 - 3);
	putchar('\n');
	return 0;
}

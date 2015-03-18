#include <cstdio>
#include <cstring>

const int maxNum = 13;
int num = 0;
int stack[3][maxNum];
int height[3];

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
		printChar(' ', num - 1);
		putchar('|');
		printChar(' ', num - 1);
	}
	else
	{
		printChar(' ', num - width - 1);
		printChar('-', width * 2 + 1);
		printChar(' ', num - width - 1);
	}
}

void printHanoi()
{
	for (int i = num - 1; i >= 0; --i)
	{
		for (int j = 0; j < 3; ++j)
		{
			putchar(' ');
			if (height[j] <= i)
			{
				printLine(-1);
			}
			else
			{
				printLine(stack[j][i] - 1);
			}
		}
		putchar('\n');
	}
	for (int j = 0; j < 3; ++j)
	{
		printChar(' ', num - 1);
		if (num == 1)
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
		printChar(' ', num - 2);
	}
	putchar('\n');
	putchar('\n');
}

void move(int from, int to)
{
	char output[100];
	sprintf(output, "Move %d from %c to %c", stack[to][height[to]++] = stack[from][--height[from]], from + 'A', to + 'A');
	int l = num * 6 - strlen(output);
	printChar('-', l / 2);
	printf("%s", output);
	printChar('-', l - l / 2);
	putchar('\n');
	putchar('\n');
	printHanoi();
}

void solve(int x, char A = 0, char B = 1, char C = 2)
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
	scanf("%d", &num);
	if (num <= 0 || num > maxNum)
	{
		printf("Invaild\n");
	}
	else
	{
		for (int i = 0; i < num; ++i)
		{
			stack[0][i] = num - i;
		}
		height[0] = num;
		height[1] = 0;
		height[2] = 0;
		printHanoi();
		solve(num);
		printChar('-', num * 3 - 3);
		printf("FINISH");
		printChar('-', num * 3 - 3);
		putchar('\n');
	}
	return 0;
}

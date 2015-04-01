#include <cstdio>
#include <cstring>

const int maxnode = 100000;
const int sigmaSize = 128;
const int cmdLength = 100;
const int modelLength = 100;
const int historyLength = 10;

const char stringFilename[] = "data";
const char stringUnknown[] = "Sorry, I don't understand your command.";
const char stringShort[] = "Sorry, it is not enough.";
const char stringUndoFailed[] = "Sorry, you cannot undo more.";

struct command
{
	char model[modelLength];
	int number;
};

int ch[maxnode][sigmaSize];
int val[maxnode];
int sz = 1;
char dfsString[modelLength];
int dfsPos;
char buf[1000];
command history[historyLength];
int historyPos = 0;
int lastHistoryPos = 0;
FILE *file;

void dfs(int u);
inline void in(char *model, int number);
inline bool out(char *model, int number);
inline void addHistory(char *model, int number);
inline void undo();
inline void save();
inline void init();
inline bool read();
inline void show();
inline void quit();
inline int max(int a, int b);
inline int c2i(char c);
inline char i2c(int x);

int main()
{
	init();
	while (1)
	{
		if (!read())
		{
			break;
		}
	}
	save();
	quit();
	return 0;
}

inline void init()
{
	printf("Commands:\nIn  : \"i <model> <number>\"\nOut : \"o <model> <number>\"\nUndo: \"u\"\nQuit: \"q\"\n");
	memset(ch[0], 0, sizeof(ch[0]));
	val[0] = 0;
	file = fopen(stringFilename, "r+");
	while (fgets(buf, 1000, file) != NULL)
	{
		char c;
		int u, v, d = 0;
		sscanf(buf, "%c%d %d %d", &c, &u, &v, &d);
		ch[u][c2i(c)] = v;
		val[v] = d;
		if (sz <= v)
		{
			sz = v + 1;
		}
	}
	fclose(file);
	show();
}

inline void quit()
{
	fclose(file);
}

inline bool read()
{
	char cmd[cmdLength];
	char model[modelLength];
	int number;
	gets(buf);
	int scanfReturn = sscanf(buf, "%s %s %d", cmd, model, &number);
	switch (cmd[0])
	{
	case 'i':
	case 'I':
		if (scanfReturn != 3 || number <= 0)
		{
			puts(stringUnknown);
			break;
		}
		in(model, number);
		addHistory(model, number);
		show();
		break;
	case 'o':
	case 'O':
		if (scanfReturn != 3 || number <= 0)
		{
			puts(stringUnknown);
			break;
		}
		if (out(model, number))
		{
			addHistory(model, -number);
			show();
		}
		else
		{
			puts(stringShort);
		}
		break;
	case 'u':
	case 'U':
		undo();
		break;
	case 'q':
	case 'Q':
		return false;
	default:
		puts(stringUnknown);
		break;
	}
	return true;
}

inline int c2i(char c)
{
	return c;
}

inline char i2c(int x)
{
	return x;
}

inline void in(char *model, int number)
{
	int u = 0;
	int l = strlen(model);
	for (int i = 0; i < l; ++i)
	{
		if (!ch[u][c2i(model[i])])
		{
			memset(ch[sz], 0, sizeof(ch[sz]));
			val[sz] = 0;
			ch[u][c2i(model[i])] = sz++;
		}
		u = ch[u][c2i(model[i])];
	}
	val[u] += number;
}

inline bool out(char *model, int number)
{
	int u = 0;
	int l = strlen(model);
	for (int i = 0; i < l; ++i)
	{
		if (!ch[u][c2i(model[i])])
		{
			return false;
		}
		u = ch[u][c2i(model[i])];
	}
	if (val[u] < number)
	{
		return false;
	}
	val[u] -= number;
	return true;
}

inline void undo()
{
	if (historyPos == lastHistoryPos)
	{
		puts(stringUndoFailed);
		return;
	}
	else
	{
		historyPos--;
		in(history[historyPos % historyLength].model, -history[historyPos % historyLength].number);
		show();
	}
}

inline void show()
{
	save();
	dfs(0);
}

void dfs(int u)
{
	if (val[u])
	{
		dfsString[dfsPos] = 0;
		printf("%s\n\tx%d\n", dfsString, val[u]);
	}
	for (int i = 0; i < sigmaSize; ++i)
	{
		if (ch[u][i])
		{
			dfsString[dfsPos++] = i;
			dfs(ch[u][i]);
			dfsPos--;
		}
	}
}

inline void save()
{
	file = fopen(stringFilename, "w+");
	for (int i = 0; i < sz; ++i)
	{
		for (int j = 0; j < sigmaSize; ++j)
		{
			if (ch[i][j])
			{
				fprintf(file, "%c%d %d", i2c(j), i, ch[i][j]);
				if (val[ch[i][j]])
				{
					fprintf(file, " %d", val[ch[i][j]]);
				}
				fprintf(file, "\n");
			}
		}
	}
	fclose(file);
}

inline void addHistory(char *model, int number)
{
	strcpy(history[historyPos % historyLength].model, model);
	history[historyPos % historyLength].number = number;
	historyPos++;
	lastHistoryPos = max(historyPos - historyLength, 0);
}

inline int max(int a, int b)
{
	return a > b ? a : b;
}

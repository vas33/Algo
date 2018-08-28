// TopologicSort.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#define MAXN 200
/* Максимален брой върхове в графа */

/* Брой върхове в графа */
const unsigned n = 8;

/* Матрица на съседство на графа */
char A[MAXN][MAXN] = {
	{ 0, 1, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 1, 0 },
	{ 0, 0, 0, 1, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 0, 0, 0, 0, 1, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0 }
};

char used[MAXN];
unsigned topsort[MAXN], total = 0;

void printSort(void)
{
	unsigned i;
	printf("Topologic sort number %u: ", ++total);
	for (i = 0; i < n; i++) printf("%u ", topsort[i] + 1);
	printf("\n");
}

void fullTopSort(unsigned count)
{
	unsigned i, j, k;
	if (count == n) { printSort(); return; }

	/* намира всички върхове без предшественик */
	for (i = 0; i < n; i++)
	{
		//проверка дали върха има предшественик
		if (!used[i]) {
			for (j = 0; j < n; j++)
				if (A[j][i]) break;
			//край проверка дали върха има предшественик

			//ако върха няма предшественик
			if (j == n) {

				//махаме връзките му към наследниците
				for (k = 0; k < n; k++) 
				{
					A[i][k] = 0;
				}

				//маркираме върха за зает
				used[i] = 1;

				//запазваме върха в списъка на на сортираните върхове
				topsort[count] = i;
				fullTopSort(count + 1); /* рекурсия */
			}
		}
	}
}

int main() {
	unsigned i;
	for (i = 0; i < n; i++) used[i] = 0;
	fullTopSort(0);

	char z;

	scanf_s(&z);
	return 0;
}


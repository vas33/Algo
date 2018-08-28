// Sequence.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <math.h>
#include <iostream>
#include  <algorithm>

using namespace std;

int lognestSequence(char* a, char* b, int n, int m)
{

	if (n  == 0  || m == 0)
	{
		return 0;
	}
	else if(a[n] == b[m])
	{
		return 1 + lognestSequence(a, b, n - 1, m - 1);
	}
	else
	{
		return std::max(lognestSequence(a, b, n , m-1), lognestSequence(a, b, n -1, m));
	}

}

int main()
{
	char sq1[] = "BAHCD";
	char sq2[] = "DBACA";


	int res = lognestSequence(sq1, sq2, strlen(sq1), strlen(sq2));

	cout << res << endl;
	char z;
	cin >> z;
    return 0;
}


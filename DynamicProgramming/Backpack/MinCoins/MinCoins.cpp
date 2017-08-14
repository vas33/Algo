// MinCoins.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <iostream>

using namespace std;

const array<int,14> coinPrices = { 5,2,2,3,2,2,2,4,3,5,8,6,7,9 };
const int sumToReach = 32;
const int numCoins = 14;

int coinsSums[sumToReach + 1][14];

bool usedCoins[sumToReach + 1][14];

int fn[100];

void Find()
{
	int maxValue = 0;
	int maxIndex = 0;
	//set used cons to zero
	memset(usedCoins, 0, sizeof(usedCoins));

	for (int i = 1; i <= sumToReach; ++i)
	{
		maxValue = maxIndex = 0;
		for (int j = 0; j < numCoins; ++j)
		{
			//sum to reach has to be biguer than coin
			//check if coin is used already
			if (coinPrices[j] <=i && !usedCoins[i - coinPrices[j]][j])
			{
				if (coinPrices[j] + fn[i - coinPrices[j]] > maxValue)
				{
					maxValue = coinPrices[j] + fn[i - coinPrices[j]];
					maxIndex = j;
				}
			}
		}

		if (maxIndex > 0)
		{
			fn[i] = maxValue;

			memcpy(usedCoins[i], usedCoins[i - coinPrices[maxIndex]], numCoins);
			usedCoins[i][maxIndex] = 1;
		}
	}
}

void PrintResult()
{
	for (int i = 0; i < numCoins; ++i)
	{
		if (usedCoins[sumToReach][i])
		{
			cout << i <<"     "<<coinPrices[i]<<"\n";
		}
	}
	cout << std::endl;
}




int main()
{
	Find();
	PrintResult();

	char z;
	cin >> z;

    return 0;
}



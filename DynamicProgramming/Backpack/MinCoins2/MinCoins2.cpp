// MinCoins2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <iostream>
#include <vector>

using namespace std;

//Given n coins with different values
//You need to find sum S with minimum coins among required
// We loop all possible decisions 
// We find the decission with smallest coins used

const int numCoins = 14;
const array<int, 14> coinPrices = { 5,2,2,3,2,2,2,4,3,5,8,6,7,9 };
const int sumToReach = 35;

int coinsSums[sumToReach + 1][14];

array<bool, numCoins> used;

int sum;
int numCoinsUsed;
int maxItemsUsed = 1000;
int bestCoinsCount = maxItemsUsed;
std::vector<int> coinsSolution;


void FindRecurse(const int index);

void FindAllCombinations()
{
	for (int i = 0;i < numCoins; ++i)
	{ 
		sum += coinPrices[i];
	}

	if (sumToReach > sum)
	{
		std::cout << "Not enough couns to make sum: " << sumToReach << std::endl;
		return;
	}

	sum = 0;

	for (int i = 0;i < numCoins; ++i)
	{
		FindRecurse(i);
	}
}
static int numCalls = 0;

void FindRecurse(const int index)
{
	//mark used
	//this index is not overflowing sum
	//num items not more than maximum
	if (sum + coinPrices[index] <= sumToReach &&
		numCoinsUsed + 1 < maxItemsUsed)
	{
		used[index] = true;
		sum += coinPrices[index];
		++numCoinsUsed;

		//skip decisions that will have more items than current best score
		if(numCoinsUsed < bestCoinsCount)
		{ 
			numCalls++;

			if (sum == sumToReach)
			{				
				bestCoinsCount = numCoinsUsed;

				coinsSolution.clear();
				//store decission
				for (int i = 0; i < numCoins;++i)
				{
					if (used[i])
					{
						coinsSolution.push_back(i);
					}
				}				
			}
			else
			{
				for (int i = 0;i < numCoins;++i)
				{
					if(!used[i])
						FindRecurse(i);
				}
			}
		}

		//go back reset coin usage
		sum -= coinPrices[index];
		used[index] = false;
		--numCoinsUsed;
	}
}

void PrintDecision()
{
	const int numCoins = coinsSolution.size();
	std::cout<< "Best Solution  for sum  " << sumToReach << " is."<< std::endl;
	std::cout << "With num coins : " << numCoins << std::endl;

	for (unsigned int i = 0; i < coinsSolution.size(); ++i)
	{
		const int indexOfCoin = coinsSolution[i];
		std::cout << " " << coinPrices[indexOfCoin] << " ";
	}

	std::cout << std::endl;
}

int main()
{
	FindAllCombinations();
	PrintDecision();

	char z;
	cin >> z;
    return 0;
}


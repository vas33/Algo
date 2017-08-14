// Backpack2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <array>
#include <iostream>

constexpr int numItems = 5;
constexpr int maxWeight = 10;

std::array<int, numItems+1> weights = {0, 1, 3, 5, 7, 9 };
std::array<int, numItems + 1> prices = {0, 2, 4, 7, 9, 10 };


int precalulated [numItems+1][maxWeight+1];


void Calculate()
{
	//zero first line of items needet for further calculations
	for (int j = 0; j <= maxWeight; ++j)
			precalulated[0][j] = 0;

	for (int i = 1; i <= numItems; ++i)
	{
		for (int j = 0; j <= maxWeight; ++j)
		{
			if (j >= weights[i] && precalulated[i - 1][j] < precalulated[i - 1][j - weights[i]] + prices[i])
			{
				precalulated[i][j] = precalulated[i - 1][j - weights[i]] + prices[i];
			}
			else
			{
				precalulated[i][j] = precalulated[i - 1][j];
			}
		}
	}

}

void PrintResults()
{
	int i = numItems, j = maxWeight;

	// i!=0 if no precise solution for problem we stop
	//otherwise i is les than zero and we crash
	while (j != 0 && i != 0)
	{
		if (precalulated[i][j] == precalulated[i-1][j])
		{
			i--;
		}
		else
		{
			std::cout << "Item: " << i << " W: "<<weights[i]<<" P: "<<prices[i]<<  std::endl;
			j -= weights[i];
			i--;
		}
	}

}

int main()
{
	Calculate();
	PrintResults();


    return 0;
}


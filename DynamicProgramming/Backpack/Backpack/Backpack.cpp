// Backpack.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

constexpr int max_weight = 70;
constexpr int num_items = 10;

int items_weights[num_items] = { 3, 5, 10, 11, 20, 7, 9, 12, 30, 2 };
int items_prices[num_items] = { 1, 1, 1,   1,  1, 1, 1, 1,   1, 1 };

int precalculated_funcs[max_weight];
bool used[max_weight][num_items];


void Calculate_Func(int weight)
{
	int currentFunction, i;
	int BestIndex, bestFunction;
	//for all items
	for (i = 1, bestFunction = 0, BestIndex = 0; i <= num_items; ++i)
	{
		//limit recursion by weight
		if (weight >= items_weights[i])
		{
			//calculate remaing weight depth first
			if (-1 == precalculated_funcs[weight - items_weights[i]])
			{
				Calculate_Func(weight - items_weights[i]);
			}

			//calculate item price at recursion bottom
			if (!used[weight - items_weights[i]][i])
			{
				currentFunction = items_prices[i] + precalculated_funcs[weight - items_weights[i]];
			}
			else
			{
				currentFunction = 0;
			}

			//get best function
			if (currentFunction > bestFunction)
			{
				BestIndex = i;
				bestFunction = currentFunction;
			}
		}
	}
	
	//at recursion end set calculated value
	precalculated_funcs[weight] = bestFunction;
	if (BestIndex > 0)
	{
		memcpy(used[weight], used[weight - items_weights[BestIndex]], num_items);
		used[weight][BestIndex] = true;
	}
}

void Calculate()
{
	memset(precalculated_funcs, -1, sizeof(precalculated_funcs));
	int sum = 0;

	for (int i = 0; i < num_items; ++i)
	{
		sum += items_weights[i];
	}

	if (sum <= max_weight)
	{
		std::cout << "We can take all " << std::endl;
		return;
	}
	Calculate_Func(max_weight);

	//print results
	for (int i = 0; i < num_items; ++i)
	{
		if (used[max_weight][i])
		{
			std::cout << " item " << i << "\n";
		}
	}

	std::cout << "max value " << precalculated_funcs[max_weight] << std::endl;
}

int main()
{
	Calculate();

	char a;
	std::cin >> a;
    return 0;
}


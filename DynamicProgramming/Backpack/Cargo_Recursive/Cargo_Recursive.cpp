// Cargo_Recursive.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <math.h>

const unsigned int numCities = 3;
const unsigned int cargoAmount = 5;
const int maxCargoAmount = 5;

unsigned int Function[numCities][cargoAmount + 1];

//zero for index 0 
//means that we can sell no cargo in some city
//in order to have better profit
const unsigned prices[numCities][cargoAmount + 1] =
{
	{ 0, 10, 15, 25, 40, 64 },
	{ 0, 15, 20, 30, 45, 60 },
	{ 0, 20, 30, 40, 50, 60 }
};

unsigned Ammount[numCities][cargoAmount];

unsigned CalcMaxCargo(unsigned City, unsigned Cargo)
{
	if (Cargo == 0)
	{
		return 0;
	}
	
	//for first city use price for cargo function
	if (City == 0)
	{
		Function[City][Cargo] = prices[City][Cargo];
	}
	// if value not set already we need to calculate it 
	else if (Function[City][Cargo] == -1)
	{
		unsigned MaxCargoCalculated = 0;
		unsigned indexForMaxCargo = 0;		

		for (unsigned cargoIndex = 0; cargoIndex <= cargoAmount; ++cargoIndex)
		{
			//make sure we don't get out of bounds
			if (cargoIndex > Cargo)
			{
				continue;
			}

			unsigned precalculatedOtherCargo = CalcMaxCargo(City - 1, cargoIndex);
			unsigned CurrentCargo = prices[City][Cargo - cargoIndex] + precalculatedOtherCargo;

			if (CurrentCargo > MaxCargoCalculated)
			{
				//store index and max cargo
				MaxCargoCalculated = CurrentCargo;
				indexForMaxCargo = cargoIndex;
			}
		}

		Function[City][Cargo] = MaxCargoCalculated;
		Ammount[City][Cargo] = indexForMaxCargo;
	}

	return Function[City][Cargo];
}

int main()
{
	//set all to -1 by default
	memset(Function, -1, sizeof(Function));
	unsigned maxCargoCalculated = CalcMaxCargo(numCities - 1, cargoAmount);
	std::cout<<"Max cargo is "<< maxCargoCalculated<<std::endl;

	char z;
	std::cin >> z;
	return 0;
}


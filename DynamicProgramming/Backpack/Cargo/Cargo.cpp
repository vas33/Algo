// Cargo.cpp : Defines the entry point for the console application.
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
const unsigned prices[numCities][ cargoAmount+1] = 
{
	{ 0, 10, 15, 25, 40, 60 },
	{ 0, 15, 20, 30, 45, 60 },
	{ 0, 20, 30, 40, 50, 60 }	
};

unsigned Ammount[numCities][cargoAmount];

void CalcIncome()
{
	//loop all cities
	for (unsigned int cityIndex = 1; cityIndex < numCities; ++cityIndex)
	{
		unsigned operationalIndex = 0;
		//for cargo amount
		for (unsigned int cargoIndex = 0; cargoIndex <= maxCargoAmount; ++cargoIndex)
		{
			//seconde cargo amount
			for (unsigned int secondCargoIndex = 0; secondCargoIndex < cargoIndex; ++secondCargoIndex)
			{
				//max cargo ammount total 5, can use all in one city
				operationalIndex = cargoIndex + secondCargoIndex;

				if (operationalIndex <= maxCargoAmount)
				{
					unsigned income =  prices[cityIndex][cargoIndex] + Function[cityIndex - 1][secondCargoIndex];
						
					if (Function[cityIndex][operationalIndex] < income)
					{
						Function[cityIndex][operationalIndex] = income;
						Ammount[cityIndex][operationalIndex] = secondCargoIndex;
					}
				}
			}
		}

	}

}

void PrintIncome()
{
	int city = numCities - 1;
	int ammount = maxCargoAmount;

	std::cout << "Best cargo income " << Function[city][maxCargoAmount] << std::endl;
	std::cout << "Amount taken from cities: " << std::endl;

	while (city >=0)
	{
		unsigned amountFromCity = ammount - Ammount[city][ammount];
		ammount = Ammount[city][ammount];
		std::cout << amountFromCity  <<" from City: "<< city<<" ,for price "<<prices[city][amountFromCity]<<std::endl;
		
		city--;
	}
}


//Complexity 
//numCities* maxCargoAmount* maxCargoAmount
// les than log(n^3) ~ log(n^2 * n/2 + n)
int main()
{	
	CalcIncome();
	PrintIncome();

	char z;
	std::cin>> z;
    return 0;
}


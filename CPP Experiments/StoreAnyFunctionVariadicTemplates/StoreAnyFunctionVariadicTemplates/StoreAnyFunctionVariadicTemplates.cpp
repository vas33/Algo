// StoreAnyFunctionVariadicTemplates.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <functional>
#include <iostream>
#include <vector>
#include <type_traits>

using functionToCall = std::function<void()>;

template<typename FunctionType, typename... FunctionArgs>
functionToCall StoreFunction(FunctionType&& func, FunctionArgs&&... args)
{
	return  std::bind(std::forward<FunctionType>(func), std::forward<FunctionArgs>(args)...);
}


void Variant()
{
	std::cout << "Variant \n";
}

void Variant2(int a, int b, int c)
{
	std::cout << "Variant2 " << a << b << c << "\n";
}

int main()
{

	std::vector<functionToCall> funcs;

	funcs.push_back(StoreFunction(&Variant));
	funcs.push_back(StoreFunction(&Variant2, 1, 2, 3));
	funcs.push_back(StoreFunction(&Variant2, 4, 5, 6));


	for (auto func : funcs)
	{
		func();
	}

	char z;
	std::cin >> z;

	return 0;
}

